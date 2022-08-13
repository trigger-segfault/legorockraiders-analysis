
import os, re
from collections import namedtuple
from typing import Dict, List, Optional, Tuple

LWS_FILEEXT = ".lws"

# Case sensitive
LWS_HEADER1 = "LWSC"
LWS_HEADER2 = "1"
LWS_FIRSTFRAME      = "FirstFrame"
LWS_LASTFRAME       = "LastFrame"
LWS_FRAMESPERSECOND = "FramesPerSecond"
LWS_PREVIEWFIRSTFRAME      = "PreviewFirstFrame"
LWS_PREVIEWLASTFRAME       = "PreviewLastFrame"
LWS_PREVIEWFRAMESPERSECOND = "PreviewFramesPerSecond"
LWS_ADDNULLOBJECT   = "AddNullObject"
# Case insensitive
LWS_SOUNDTRIGGERPREFIX    = "SFX"
LWS_SOUNDTRIGGERSEPERATOR = ","
LWS_SOUNDTRIGGERRANGE     = "-"

Lws_Info = namedtuple('Lws_Info', ('path', 'first', 'last', 'fps', 'triggers'))
Lws_SoundTrigger = namedtuple('Lws_SoundTrigger', ('sfx', 'frames'))

# SPACES = (' ', '\n', '\t', '\v', '\f', '\r')

# def isspace(c:str):
#     return c in SPACES

def splitws(text:str):
    # Normalize whitespace and combine repeats into a single character
    normtext = re.sub(r"[ \n\t\v\f\r]+", ' ', text)
    #if re.search(r"[ \n\t\v\f\r]{2,}", normtext) is not None: raise Exception("Whitespace not properly normalized")
    #assert(re.search(r"[ \n\t\v\f\r]{2,}", normtext) is None),"Whitespace not properly normalized"
    return normtext.split(' ')

def lws_parse_trigger(text:str) -> Optional[Lws_SoundTrigger]:
    tokens = text.split(LWS_SOUNDTRIGGERSEPERATOR)
    if len(tokens) < 3: return None # Can't parse this trigger
    #
    sfx = tokens[1]
    frames = []
    #
    for token in tokens[2:]:
        dash = token.find(LWS_SOUNDTRIGGERRANGE)
        if dash != -1:
            # Use strip because of how lenient atoi is
            start = int(token[:dash].strip())
            end = int(token[dash+1:].strip())
        else:
            start = end = int(token.strip())
        frames.append((start, end))
    return Lws_SoundTrigger(sfx, frames)

def lws_is_trigger(text:str) -> bool:
    # Case insensitive
    text = text.upper()
    return (text.startswith(LWS_SOUNDTRIGGERPREFIX.upper()) and
            text.startswith(LWS_SOUNDTRIGGERSEPERATOR.upper(), len(LWS_SOUNDTRIGGERPREFIX)))

def lws_check_header(lines:List[str]) -> bool:
    return len(lines) >= 2 and lines[0] == LWS_HEADER1 and lines[1] == LWS_HEADER2

def lws_parse(path:str) -> Optional[Lws_Info]:
    with open(path, 'r', encoding='ascii') as f:
        lines = [l.rstrip('\r\n') for l in f.readlines()]
    #
    if not lws_check_header(lines):
        return Ellipsis # Not an LWS file
    #
    firstFrame      = 0
    lastFrame       = 0
    framesPerSecond = 0
    triggers = [] # type: list[Lws_SoundTrigger]
    #
    for line in lines:
        tokens = splitws(line)
        if len(tokens) < 2: continue # Can't parse this line
        #
        cmd = tokens[0]
        if   cmd == LWS_FIRSTFRAME:      firstFrame      = int(tokens[1])
        elif cmd == LWS_LASTFRAME:       lastFrame       = int(tokens[1])
        elif cmd == LWS_FRAMESPERSECOND: framesPerSecond = float(tokens[1])
        elif cmd == LWS_ADDNULLOBJECT:
            text = line[len(LWS_ADDNULLOBJECT) + 1:]
            if lws_is_trigger(text):
                trigger = lws_parse_trigger(text)
                if trigger is not None:
                    triggers.append(trigger)
    #
    return Lws_Info(path, firstFrame, lastFrame, framesPerSecond, triggers)


def scanfiles(basedir:str, count:Optional[int]=None) -> List[Lws_Info]:
    lwsfiles = []
    scenes = []
    # Scan potential lws files
    for relpath,dirs,files in os.walk(basedir):
        for file in files:
            if os.path.splitext(file.lower())[1] == LWS_FILEEXT:
                if count is not None and count <= 0:
                    break
                lwsfile = os.path.join(relpath, file)
                lwsfiles.append(lwsfile)
                if count is not None:
                    count -= 1
        if count is not None and count <= 0:
            break
    #
    # Parse found lws files
    #badHeaders = []
    for lwsfile in lwsfiles:
        print(f'Scanning: {lwsfile}')
        scene = lws_parse(lwsfile)
        #if scene is Ellipsis:
        #    badHeaders.append(lwsfile)
        if scene is not None and scene is not Ellipsis:
            scenes.append(scene)
    #
    #print(f'{len(badHeaders)} lws files with invalid headers')
    return scenes



def main(args:list=None):
    if args is None:
        import sys
        args = sys.argv[1:]

    basedir = args[0] if args else '.'
    scenes = scanfiles(basedir)
    sfxScenes = [s for s in scenes if s.triggers]
    print(f'{len(sfxScenes)} / {len(scenes)} scenes have sound triggers')
    firstEqLast = [s for s in scenes if s.first == s.last]
    lastIsZero = [s for s in scenes if s.last == 0]
    print(f'{len(firstEqLast)} scenes with FirstFrame == LastFrame')
    print(f'{len(lastIsZero)} scenes with LastFrame == 0')
    #
    sfxFirstEqLast = [s for s in firstEqLast if s in sfxScenes]
    sfxLastIsZero = [s for s in lastIsZero if s in sfxScenes]
    print(f'{len(sfxFirstEqLast)} ST scenes with FirstFrame == LastFrame')
    print(f'{len(sfxLastIsZero)} ST scenes with LastFrame == 0')
    sfxOnLast = []
    for s in sfxScenes:
        found = False
        for t in s.triggers:
            for f in t.frames:
                if f[0] == s.last:
                    if not found:
                        found = True
                        print(s.path)
                    print(t)
                    if s not in sfxOnLast: sfxOnLast.append(s)
    print(f'{len(sfxOnLast)} scenes with SFX where frameStart == LastFrame')
        


if __name__ == '__main__':
    exit(main())
