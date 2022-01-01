
# from collections import namedtuple
class CryShift(list):
    # table:list
    # def __init__(self, table:list=None):
    #     self.table = table if table is not None else ([0] * 6)
    def __str__(self): return '[' + ','.join(f'{n:>2d}' for n in self) + ']' # f'CryShift({self.table})'
    __repr__ = __str__
    # def __getitem__(self, key): return self.table[]

class CryTuple:
    cryCount:int
    unkCount:int
    def __init__(self, cryCount:int=0, unkCount:int=0):
        self.cryCount = cryCount
        self.unkCount = unkCount
    def __str__(self): return f'({self.cryCount:>2d},{self.unkCount:>2d})'
    __repr__ = __str__

CRYDEBUG = True

# CryShift = namedtuple('CryShift', ('table',))
# s_CryShift_Table = [CryShift([0 for __ in range(6)]) for _ in range(2)]
s_CryShift_Table = [CryShift([0 for __ in range(6)]) for _ in range(2)]

def drawcry(crystals:int, usedCrystals:int, quota:int=None):
    # from collections import namedtuple
    # CryTuple = namedtuple('CryTuple', ('cryCount', 'unkCount'))
    tableCounts = [[CryTuple(0,0) for __ in range(6)] for _ in range(2)]
    baseCounts = [0, 0]
    def logTables(idx=None):
        if not CRYDEBUG: return
        for i in range(0 if idx is None else idx, 2 if idx is None else (idx + 1)):
            print(f'[{baseCounts[i]:>2d} : {tableCounts[i]} : {s_CryShift_Table[i]}')
    #
    # s_CryShift_Table[0].table[5] = crystals
    # s_CryShift_Table[1].table[5] = usedCrystals
    for j in range(5):
        for i in range(2):
            # s_CryShift_Table[i].table[j] = s_CryShift_Table[i].table[j + 1]
            s_CryShift_Table[i][j] = s_CryShift_Table[i][j + 1]
    s_CryShift_Table[0][5] = crystals
    s_CryShift_Table[1][5] = usedCrystals
    #
    baseCounts[0] = 0
    baseCounts[1] = 0
    tableCounts[0][0].cryCount = 0
    #
    for i in range(2):
        for j in range(6):
            k = 0
            for _ in range(baseCounts[i]):
                # if tableCounts[i][k].cryCount == s_CryShift_Table[i].table[j]:
                if tableCounts[i][k].cryCount == s_CryShift_Table[i][j]:
                    tableCounts[i][k].unkCount += 1
                    break
                k += 1
            if k == baseCounts[i]:
                # tableCounts[i][k].cryCount = s_CryShift_Table[i].table[j]
                tableCounts[i][k].cryCount = s_CryShift_Table[i][j]
                tableCounts[i][k].unkCount = 1
                baseCounts[i] += 1
            del k
    #
    logTables()
    #
    for i in range(2):
        maxFound = 0
        for k in range(baseCounts[i]):
            # if tableCounts[i][k].cryCount == s_CryShift_Table[i].table[k]:
            if maxFound < tableCounts[i][k].unkCount:
                maxFound = tableCounts[i][k].unkCount
                if i == 0:
                    crystals     = tableCounts[i][k].cryCount
                else:
                    usedCrystals = tableCounts[i][k].cryCount
        del maxFound
    #
    # print(f'Crystals: {crystals}')
    #
    unusedCrystals = crystals
    if quota: # is not None:
        unusedCrystals     = min(quota, unusedCrystals)
        usedCrystals = min(quota, usedCrystals)
    #
    cryDisplay = [' ' for _ in range(26)]
    destPos = 25
    #
    R  = '\x1b[0m'
    B  = '\x1b[48;2;55;55;55m'
    CU = '\x1b[37;1m'
    CG = '\x1b[32;1m'
    CX = '\x1b[30m'
    F  = CU #'\x1b[30m'
    CHR = '&'
    #
    for j in range(usedCrystals):
        cryDisplay[destPos] = f'{B}{CU}{CHR}{R}{B}'
        destPos -= 1
    #
    for j in range(max(0, unusedCrystals - usedCrystals)):
        cryDisplay[destPos] = f'{B}{CG}{CHR}{R}{B}'
        destPos -= 1
    
    # if quota is not None:
    for j in range(max(0, (quota or 26) - unusedCrystals)):
        cryDisplay[destPos] = f'{B}{CX}{CHR}{R}{B}'
        destPos -= 1
    #
    # print(f'\x1b[48;2;55;55;55m[{str(crystals).center(3)}] ' + ' '.join(cryDisplay) + ' \x1b[0m')
    logTables()
    print(f'{B}{F}[{R}{B}{crystals:>3d}{R}{B}{F}|{R}{B} ' + ' '.join(cryDisplay) + f' {R}{B}{F}]{R}')
    # if CRYDEBUG:
    #     for i in range(2):
    #         print(f'[{baseCounts[i]:>2d} : {tableCounts[i]} : {s_CryShift_Table[i]}')
    #     # print(baseCounts)
    #     # print(tableCounts)
    #     # print(s_CryShift_Table)

drawcry(11, 3, 15)
drawcry(11, 3, 15)
drawcry(11, 3, 15)
