
def parse_flags(flagsdic:dict, text:str, fallbackdic:dict=None):
    value = 0
    text = text.strip() # Remove extra whitespace at start
    parts = text.lstrip('(').rstrip(';').rstrip().rstrip(')').split('|') # remove surrounding parens and split
    for p in parts:
        p =  p.strip() # remove newlines and indentation
        try:
            value |= flagsdic[p]
        except KeyError:
            if fallbackdic is not None and p in fallbackdic:
                value |= fallbackdic[p]
            else:
                raise
    return f'0x{value:08x}'

