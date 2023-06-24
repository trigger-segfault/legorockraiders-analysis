#!/usr/bin/env python3
#-*- coding: utf-8 -*-
"""Track how many functions of how many modules have been implemented in OpenLRR.
"""

__version__ = '0.0.1'
__date__    = '2023-06-23'
__author__  = 'Robert Jordan'

__all__ = ['main']

#######################################################################################

import os, re
from functools import cmp_to_key
from typing import List, Optional, Pattern


#######################################################################################

PAT_COMMENT:str = r"""
(?P<comment>\/\/[ \t]*<LegoRR\.exe[ \t]*@[A-Fa-f0-9]{8}>)\n # Function location comment
"""

PAT_DEFINE:str = r"""
\#define[ \t]+(?P<name>[A-Za-z_][A-Za-z_0-9]*)[ \t]* # define keyword and function name
\(\((?:NERPsFunction| # NERPsFunctions.h has special defines for functions
    (?P<return>[^()]+?)[ \t]* # Return value
    \([ \t]*?(?P<call>__[a-z_]+)[ \t]*?\*[ \t]*\)[ \t]*? # Calling convention
    (?P<args>\((?:[^()]|\([^()]*\))*\)) # Function arguments
)\)0x[A-Fa-f0-9]{8}\)[ \t]*
"""

RE_FUNCDEFINE:Pattern = re.compile(rf"""
{PAT_COMMENT} # Function location comment
{PAT_DEFINE}
""", re.VERBOSE | re.MULTILINE)

RE_FUNCDECLARE:Pattern = re.compile(rf"""
{PAT_COMMENT} # Function location comment
(?:\/\/[ \t]*{PAT_DEFINE}\n)? # Define might have already been removed, but might still be present
(?!extern)(?:(?:__)?inline|[^#\/\n]+__cdecl[^\n]*) # Avoid extern globals and match inline or __cdecl calling convention
""", re.VERBOSE | re.MULTILINE)


#######################################################################################

class BaseProgress:
    def __init__(self, path:str):
        self.path = path

    @property
    def total(self) -> int:
        return self.unimplemented + self.implemented
    @property
    def percent(self) -> float:
        return self.implemented / self.total

    @property
    def total_modules(self) -> int:
        return self.unimplemented_modules + self.implemented_modules
    @property
    def percent_modules(self) -> float:
        return self.implemented_modules / self.total_modules

    @property
    def inprogress(self) -> bool:
        return self.unimplemented > 0 and self.implemented > 0
    @property
    def completed(self) -> bool:
        return self.unimplemented == 0


class ModuleProgress(BaseProgress):
    def __init__(self, path:str):
        super().__init__(path)
        self.unimplemented = 0
        self.implemented   = 0
        
        with open(self.path, 'rt', encoding='utf-8') as f:
            text = f.read()
        self.unimplemented = len(RE_FUNCDEFINE.findall(text))
        self.implemented   = len(RE_FUNCDECLARE.findall(text))

    @property
    def name(self) -> str:
        return os.path.splitext(os.path.basename(self.path))[0]
    @property
    def isfolder(self) -> bool:
        return False

    @property
    def unimplemented_modules(self) -> int:
        return 0 if self.completed else 1
    @property
    def implemented_modules(self) -> int:
        return 1 if self.completed else 0


class FolderProgress(BaseProgress):
    def __init__(self, path:str, exclude_names:Optional[List[str]]=None):
        super().__init__(path)
        self.children = []

        if exclude_names is None: exclude_names = []
        else:                     exclude_names = [e.lower() for e in exclude_names]

        for file in os.listdir(self.path):
            filepath = os.path.join(self.path, file)
            child = None
            if os.path.isfile(filepath):
                # Only read C header files.
                if filepath.lower().endswith('.h'):
                    if os.path.splitext(file.lower())[0] not in exclude_names:
                        child = ModuleProgress(filepath)
            elif os.path.isdir(filepath):
                if (file.lower() + '/') not in exclude_names:
                    child = FolderProgress(filepath, exclude_names=exclude_names)
            
            # Exclude empty modules / folders from the list.
            if child is not None and child.total > 0:
                self.children.append(child)
        
        self.sort(full=False)
    
    def _sort(self, sortfunc, full:bool) -> None:
        self.children.sort(key=cmp_to_key(sortfunc))
        if full:
            for child in self.children:
                if child.isfolder:
                    child._sort(sortfunc, full=full)

    def sort(self, full:bool=True) -> None:
        def _sortfunc(a, b):
            if a.isfolder != b.isfolder:
                return -1 if a.isfolder else 1
            else:
                return -1 if a.name.lower() < b.name.lower() else 1
        
        self._sort(_sortfunc, full=full)
    
    def sort_by_unimplemented(self, full:bool=True) -> None:
        def _sortfunc_unimplemented(a, b):
            # if a.isfolder != b.isfolder:
            #     return -1 if a.isfolder else 1
            if a.unimplemented != b.unimplemented:
                return -1 if a.unimplemented > b.unimplemented else 1
            else:
                return -1 if a.name.lower() < b.name.lower() else 1
        
        self._sort(_sortfunc_unimplemented, full=full)

    def sort_by_percent(self, full:bool=True) -> None:
        def _sortfunc_percent(a, b):
            # if a.isfolder != b.isfolder:
            #     return -1 if a.isfolder else 1
            if a.percent != b.percent:
                return -1 if a.percent < b.percent else 1
            elif a.unimplemented != b.unimplemented:
                return -1 if a.unimplemented > b.unimplemented else 1
            else:
                return -1 if a.name.lower() < b.name.lower() else 1
        
        self._sort(_sortfunc_percent, full=full)

    
    def flatten(self) -> None:
        newchildren = []
        for child in self.children:
            if not child.isfolder:
                newchildren.append(child)
            else:
                child.flatten()
                newchildren.extend(child.children)
        self.children.clear()
        self.children.extend(newchildren)
    
    @property
    def name(self) -> str:
        return os.path.basename(self.path) + '/'
    @property
    def isfolder(self) -> bool:
        return True
    
    @property
    def unimplemented(self) -> int:
        return sum([child.unimplemented for child in self.children])
    @property
    def implemented(self) -> int:
        return sum([child.implemented for child in self.children])
    
    @property
    def unimplemented_modules(self) -> int:
        return sum([child.unimplemented_modules for child in self.children])
    @property
    def implemented_modules(self) -> int:
        return sum([child.implemented_modules for child in self.children])


class ProgressPrinter:
    def __init__(self):
        self.indent           = 4
        self.module_progress  = False
        self.hide_implemented = False
        self.hide_modules     = False
        self.color            = False

        self._maxdepth  = 0
        self._maxlength = 0
    
    def print(self, item:BaseProgress) -> None:
        self._maxdepth  = self._getmaxdepth(item, 0) - (1 if self.hide_modules else 0) # -1 to skip depth added by modules
        self._maxlength = self._getmaxlength(item, 0)

        self._print_item(item, 0)

    def _print_item(self, item:BaseProgress, level:int) -> None:
        if not item.isfolder and (self.hide_modules or (self.hide_implemented and item.completed)):
            return # Skip this module
        
        indentstr = ' ' * (level * self.indent)
        namestr = f'{indentstr}{item.name}'.ljust(self._maxlength + level)
        dashstr = '-' * (self._maxdepth - level)

        module_progress = item.isfolder and self.module_progress
        implemented = item.implemented_modules if module_progress else item.implemented
        total       = item.total_modules       if module_progress else item.total
        percent     = item.percent_modules     if module_progress else item.percent

        colorstart = colorend = color2start = color2end = ''
        if self.color:
            colorend = color2end = '\x1b[0m' # Reset
            
            colorstart = '\x1b['
            if item.completed:    colorstart += '32' # Green
            elif item.inprogress: colorstart += '33' # Yellow
            else:                 colorstart += '31' # Red
            if not item.isfolder: colorstart += ';1' # Bright (bold)
            colorstart += 'm'

            if module_progress: color2start = '\x1b[34;1m' # Blue
            else:               color2start = '\x1b[36;1m' # Cyan

        print(f'{colorstart}{namestr}{colorend} {dashstr} {color2start}{implemented:>4}/{total:>4}{color2end}  ({percent*100:>5.1f}%)')

        if item.isfolder:
            # Print children
            for child in item.children:
                self._print_item(child, level+1)

    # Helper functions for printing.
    def _getmaxdepth(self, item:BaseProgress, level:int) -> int:
        depth = level + 1
        if item.isfolder and item.children:
            return max([depth] + [self._getmaxdepth(child, level+1) for child in item.children])
        return depth

    def _getmaxlength(self, item:BaseProgress, level:int) -> int:
        length = level * self.indent + len(item.name)
        if item.isfolder and item.children:
            return max([length] + [self._getmaxlength(child, level+1) for child in item.children])
        return length


#######################################################################################

#region ## MAIN FUNCTION ##

def main(argv:Optional[list]=None) -> int:
    import os

    #region ## PARSER SETUP ##
    import argparse
    parser = argparse.ArgumentParser(
        description='OpenLRR decompilation progress reporter',
        epilog='The default method shows progress by number of functions implemented.',
        add_help=True)

    parser.add_argument('input', metavar='FOLDER', help='folder to scan for progress')

    # Visual
    parser.add_argument('-i', '--indent', action='store', type=int, default=4, help='indent spacing of folder structure tree')
    parser.add_argument('-c', '--color', action='store_true', default=False, help='print with color')
    # Organization
    parser.add_argument('-m', '--modules', dest='module_progress', action='store_true', default=False, help='show module progress for folders')
    parser.add_argument('-f', '--folders', dest='hide_modules', action='store_true', default=False, help='only show folders')
    parser.add_argument('-u', '--unimplemented', dest='hide_implemented', action='store_true', default=False, help='hide implemented modules')
    parser.add_argument('-F', '--flatten', action='store_true', default=False, help='hide all subfolders and just show modules')
    # Sorting
    parser.add_argument('-P', '--sort-percent', dest='sort_by_percent', action='store_true', default=False, help='sort by lowest implemented percentage')
    parser.add_argument('-U', '--sort-unimplemented', dest='sort_by_unimplemented', action='store_true', default=False, help='sort by most unimplemented functions')

    #endregion

    ###########################################################################

    #region ## PARSER VALIDATION ##

    args = parser.parse_args(argv)

    exclude_names = [
        'common', 'dllmain', 'hook', 'interop', 'legacy', 'OpenLRR',
        'Debug', 'GameCommon', 'Shortcuts',
        'cmdline/', 'platform/'
    ]

    #endregion

    ###########################################################################

    # Read folder structure and header files.
    basedir = FolderProgress(args.input, exclude_names=exclude_names)
    if args.flatten:
        basedir.flatten()
    if args.sort_by_unimplemented:
        basedir.sort_by_unimplemented()
    elif args.sort_by_percent:
        basedir.sort_by_percent()

    printer = ProgressPrinter()
    printer.indent           = args.indent
    printer.module_progress  = args.module_progress
    printer.hide_modules     = args.hide_modules
    printer.hide_implemented = args.hide_implemented
    printer.color            = args.color
    printer.print(basedir)

    return 0


#endregion


###########################################################################

del List, Optional, Pattern  # cleanup declaration-only imports


## MAIN CONDITION ##

if __name__ == '__main__':
    exit(main())
