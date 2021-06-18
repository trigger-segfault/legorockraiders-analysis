#!/usr/bin/env python3
#-*- coding: utf-8 -*-
"""Deploy finished changes in vscode-lrr plugin to VSCode extensions directory
"""

__version__ = '0.1.0'
__date__    = '2021-04-18'
__author__  = 'Robert Jordan'

#######################################################################################

## CONFIGURABLE DEFAULTS ##
import os

USER_DIR:str = os.path.expanduser("~")  # '~' works on Windows for this func
EXTENSION_DIR:str = r".vscode/extensions/vscode-lrr"
EXTENSION_PATH:str = os.path.join(USER_DIR, EXTENSION_DIR)

#NOTE: assumes this script is in the plugin directory with the extension folder
SCRIPT_DIR:str = os.path.abspath(os.path.dirname(__file__))
PLUGIN_PATH:str = os.path.join(SCRIPT_DIR, r"vscode-lrr")

IGNORE_FILES:list = ["_backup"]
IGNORE_EXTS:list  = []

#######################################################################################

import hashlib, os, shutil, re
from types import SimpleNamespace
from collections import namedtuple

## CHANGES NAMED TUPLE ##

Changes = namedtuple('Changes', ('add', 'remove', 'change', 'older', 'same'))

## PATH/FILE HELPERS ##

def replace_sep(path:str, normsep:str) -> str:
    if not normsep:
        return path
    return path.replace('\\', normsep).replace('/', normsep)

def strip_curdir_dot(reldir:str) -> str:
    if reldir in ('', '.', './', '.\\'):
        return ''
    elif len(reldir) > 2 and reldir[:2] in ('./','.\\'):
        return reldir[2:]
    else:
        return reldir

def join_relpath(basedir:str, reldir:str) -> str:
    if not basedir and not reldir: return '.'
    elif not basedir: return reldir
    elif not reldir:  return basedir

    if reldir == '.':
        return basedir
    elif len(reldir) > 2 and reldir[:2] in ('./','.\\'):
        return os.path.join(basedir, reldir[2:])
    else:
        return os.path.join(basedir, reldir)

def hash_file(filename:str) -> bytes:
    with open(filename, 'rb') as f:
        return hashlib.md5(f.read()).digest()

## FIND CHANGES ##

def walk_changes(srcdir:str, dstdir:str, ignore_files:tuple=(), ignore_exts:tuple=(), *, normsep:str=None) -> Changes:
    """Changes include change in case
    """
    ignore_files = set(os.path.normcase(f) for f in ignore_files)
    ignore_exts  = set(os.path.normcase(e) for e in ignore_exts)

    changes:Changes = Changes([], [], [], [], [])

    stack:list = ['.']
    while stack:
        curdir = stack.pop(0)
        srcpath = join_relpath(srcdir, curdir)
        dstpath = join_relpath(dstdir, curdir)

        srcfiles:list = os.listdir(srcpath) if os.path.isdir(srcpath) else []
        dstfiles:list = os.listdir(dstpath) if os.path.isdir(dstpath) else []
        srcnorm:list = [os.path.normcase(s) for s in srcfiles]
        dstnorm:list = [os.path.normcase(d) for d in dstfiles]

        def srccase(fnorm:str) -> str:
            return srcfiles[srcnorm.index(fnorm)]
        def dstcase(fnorm:str) -> str:
            return dstfiles[dstnorm.index(fnorm)]

        for f in set(srcnorm + dstnorm):
            src_exist = f in srcnorm
            dst_exist = f in dstnorm
            _, ext = os.path.splitext(f)
            if f in ('.', '..') or f in ignore_files or ext in ignore_exts:
                continue
            
            src_rel = join_relpath(curdir, srccase(f)) if src_exist else ''
            dst_rel = join_relpath(curdir, dstcase(f)) if dst_exist else ''
            src_file = os.path.join(srcpath, srccase(f)) if src_exist else ''
            dst_file = os.path.join(dstpath, dstcase(f)) if dst_exist else ''
            if src_exist and dst_exist:
                #NOTE: don't solve for dir vs. file conflicts,  just complain :)
                assert(os.path.isdir(src_file) == os.path.isdir(dst_file)), f"source and destination conflict file vs. directory attribute\n{src_file}\n{dst_file}"

            if src_exist and os.path.isdir(src_file):
                stack.append(src_rel)  # another folder to scan
            elif dst_exist and os.path.isdir(dst_file):
                stack.append(dst_rel)  # another folder to scan
            elif not dst_exist:
                changes.add.append(strip_curdir_dot(src_rel))  # add source file
            elif not src_exist:
                changes.remove.append(strip_curdir_dot(dst_rel))  # remove dest file
            elif srccase(f) != dstcase(f):
                changes.change.append(strip_curdir_dot(src_rel))  # change in case (files only)
            else:
                src_mtime = os.stat(src_file).st_mtime
                dst_mtime = os.stat(dst_file).st_mtime
                if hash_file(src_file) == hash_file(dst_file):
                    changes.same.append(strip_curdir_dot(src_rel))  # same MD5 hash
                elif src_mtime >= dst_mtime:
                    changes.change.append(strip_curdir_dot(src_rel))  # newer source file
                else:
                    changes.older.append(strip_curdir_dot(src_rel))   # older source file

    # normalize and sort
    for files in changes:  # tuple, so we can iterate through each list
        files.sort()
        if normsep:
            for i,f in enumerate(files):
                # ultra-lazy
                files[i] = replace_sep(f, normsep)

    return changes

#######################################################################################

## COLOR SETUP ##
try:
    import colorama
    from colorama import Fore, Style
    colorama.init()  # comment out init if extended color support is needed in Windows Terminal
except ImportError:
    # dummy color namespaces for disabled color
    Fore = SimpleNamespace(RESET='', BLACK='', BLUE='', CYAN='', GREEN='', MAGENTA='', RED='', WHITE='', YELLOW='', LIGHTBLACK_EX='', LIGHTBLUE_EX='', LIGHTCYAN_EX='', LIGHTGREEN_EX='', LIGHTMAGENTA_EX='', LIGHTRED_EX='', LIGHTWHITE_EX='', LIGHTYELLOW_EX='')
    Style = SimpleNamespace(RESET_ALL='', BRIGHT='', DIM='', NORMAL='') #, BOLD='', ITALIC='', UNDERLINE='', BLINKING='', INVERSE='', INVISIBLE='', STRIKETHROUGH='')
C = SimpleNamespace(**Fore.__dict__, **Style.__dict__)

#######################################################################################

## MAIN FUNCTION ##

def main(argv:list=None) -> int:
    ## PARSER SETUP ##
    import argparse
    parser = argparse.ArgumentParser(
        description='deploy changes to vscode-lrr extension',
        add_help=True)

    parser.add_argument('-p', '--preview', action='store_true', default=False, required=False, help='preview changes')
    parser.add_argument('-u', '--update', action='store_true', default=False, required=False, help='update changed: updated and added files')
    parser.add_argument('-o', '--older', action='store_true', default=False, required=False, help='update changes: where source file is older')
    parser.add_argument('-r', '--remove', action='store_true', default=False, required=False, help='update changes: removed files')

    parser.add_argument('-T', '--test', action='store_true', default=False, required=False, help='test mode: print operations that *would* happen to files')

    args = parser.parse_args(argv)

    #if not args.test and not args.preview and not args.update and not args.older and not args.remove:
    #NOTE: are any args passed? (only works if all args default to False, otherwise use above line)
    if not [v for v in args.__dict__.values() if v]:
        # no arguments, print help :)
        parser.print_help()
        return 1
        
    ## FIND CHANGES ##
    plugin_dir = PLUGIN_PATH
    deploy_dir = EXTENSION_PATH
    ignore_files = IGNORE_FILES
    ignore_exts  = IGNORE_EXTS
    normsep = '/'
    changes:Changes = walk_changes(plugin_dir, deploy_dir, ignore_files, ignore_exts, normsep=normsep)

    ## HANDLE CHANGES TYPE FUNCTION ##
    def do_changes(name:str, color:str, files:list, action:str, condition:bool) -> int:
        color = color or ''
        reset = f'{C.RESET_ALL}' if color else ''

        preview = args.preview
        test = args.test
        if not preview and not condition:
            return 0

        num_changes:int = 0
        print(f'{C.BRIGHT}{C.WHITE}[{name}]{C.RESET_ALL}')
        for f in files:
            if condition and action is not None:
                src_file = replace_sep(os.path.join(plugin_dir, f), normsep)
                dst_file = replace_sep(os.path.join(deploy_dir, f), normsep)
                dst_dir  = replace_sep(os.path.dirname(dst_file), normsep)

                if action == 'add':
                    if os.path.isfile(dst_file):
                        raise Exception(f'unexpected: destination file exists:\n{dst_file}')
                    if not os.path.exists(dst_dir):
                        if test: print(f'os.makedirs(\n "{dst_dir}")')
                        else:         os.makedirs(dst_dir)
                    if test:          print(f'shutil.copy(\n "{src_file}",\n "{dst_file}")')
                    elif not preview: shutil.copy(src_file, dst_file)
                    num_changes += 1

                elif action == 'remove':
                    if not os.path.isfile(dst_file):
                        raise Exception(f'unexpected: destination file does not exist:\n{dst_file}')
                    if test:          print(f'os.remove(\n "{dst_file}")')
                    elif not preview: os.remove(dst_file)
                    num_changes += 1

                elif action == 'update':
                    if not os.path.isfile(dst_file):
                        raise Exception(f'unexpected: destination file does not exist:\n{dst_file}')
                    if test:          print(f'shutil.copy(\n "{src_file}",\n "{dst_file}")')
                    elif not preview: shutil.copy(src_file, dst_file)
                    num_changes += 1

            print(f'{color}{f}{reset}')
        print()
        return num_changes
        
    ## DO THE THING ##
    other = removed = added = updated = 0
    added   += do_changes('Added',   f'{C.BRIGHT}{C.GREEN}',  changes.add,    'add',    args.update)
    removed += do_changes('Removed', f'{C.BRIGHT}{C.RED}',    changes.remove, 'remove', args.remove)
    updated += do_changes('Changed', f'{C.BRIGHT}{C.YELLOW}', changes.change, 'update', args.update)
    updated += do_changes('Older',   f'{C.DIM}{C.YELLOW}',    changes.older,  'update', args.older)
    other   += do_changes('Same',    f'{C.BRIGHT}{C.BLACK}',  changes.same,   None,     False)

    total = removed + added + updated + other

    msg = ''.join([ f'{C.BRIGHT}{C.CYAN}{total} change(s){C.RESET_ALL} to files ',
                    f'{C.BRIGHT}{C.WHITE}[',
                    f'{C.GREEN}add: {added}{C.RESET}, ',
                    f'{C.RED}rem: {removed}{C.RESET}, ',
                    f'{C.YELLOW}upd: {updated}{C.RESET}',
                    f']{C.RESET_ALL}' ])
    if args.test:
        print(f'{C.BRIGHT}{C.BLUE}<TESTING>{C.RESET_ALL} Would perform {msg}')
    elif args.preview:
        print(f'{C.BRIGHT}{C.BLUE}<PREVIEW>{C.RESET_ALL} Would perform {msg}')
    else:
        print(f'Performed {msg}')

    return 0


## MAIN CONDITION ##

if __name__ == '__main__':
    exit(main())

