


def real2log(volf:float) -> int:
    import math
    volf = max(0.0, min(1.0, float(volf))) # clamp
    vol = round(math.log10(100.0 - (volf * 99)) * -5000.0) # convert
    return max(-10000, min(0, vol)) # clamp

def log2real(vol:int) -> float:
    import math
    vol = max(-10000, min(0, vol)) # clamp
    volf = ((100.0 - math.pow(10.0, (vol / -5000.0))) / 99.0) # convert
    return max(0.0, min(1.0, float(volf))) # clamp


def real2log2(volf:float) -> int:
    import math
    volf = max(0.0, min(1.0, float(volf))) # clamp
    vol = round(math.log10(10.0 - (volf * 9)) * -10000.0) # convert
    return max(-10000, min(0, vol)) # clamp

def log2real2(vol:int) -> float:
    import math
    vol = max(-10000, min(0, vol)) # clamp
    volf = ((10.0 - math.pow(10.0, (vol / -10000.0))) / 9.0) # convert
    return max(0.0, min(1.0, float(volf))) # clamp


def real2logx(x:float, volf:float) -> int:
    import math
    volMax    = float(x)
    volRange  = volMax - 1.0
    volScalar = -10000 / math.log10(volMax)
    #
    volf = max(0.0, min(1.0, float(volf))) # clamp
    vol = round(math.log10(volMax - (volf * volRange)) * volScalar) # convert
    return max(-10000, min(0, vol)) # clamp

def log2realx(x:float, vol:int) -> float:
    import math
    volMax    = float(x)
    volRange  = volMax - 1.0
    volScalar = -10000 / math.log10(volMax)
    #
    vol = max(-10000, min(0, vol)) # clamp
    volf = ((volMax - math.pow(10.0, (vol / volScalar))) / volRange) # convert
    return max(0.0, min(1.0, float(volf))) # clamp


def real2logx2(x:float, volf:float) -> int:
    import math
    volMax    = float(x)
    volRange  = volMax - 1.0
    volScalar = -10000 / math.log10(volMax)
    #
    volf = max(0.0, min(1.0, float(volf))) # clamp
    vol = round(math.log10(volMax - ((1.0 - volf) * volRange)) * volScalar) # convert
    return max(-10000, min(0, vol)) # clamp

def log2realx2(x:float, vol:int) -> float:
    import math
    volMax    = float(x)
    volRange  = volMax - 1.0
    volScalar = -10000 / math.log10(volMax)
    #
    vol = max(-10000, min(0, vol)) # clamp
    volf = 1.0 - ((volMax - math.pow(10.0, (vol / volScalar))) / volRange) # convert
    return max(0.0, min(1.0, float(volf))) # clamp

def p2m(volf:float) -> int:
    import math
    attenuation = 1.0 / 1024.0 + (volf / 100.0) * 1023.0 / 1024.0
    db = 10 * math.log(attenuation, 2)# / math.log10(2)
    return round(db * 100)

def m2p(vol:int) -> float:
    import math
    exponent = ((vol / 1000.0) + 10)
    numerator = 100.0 * (math.pow(2, exponent) - 1)
    return numerator / 1023.0


def p2m2(volf:float) -> int:
    import math
    attenuation = 1.0 / 1024.0 + (volf) * 1023.0 / 1024.0
    db = 10 * math.log(attenuation, 2)# / math.log10(2)
    return round(db * 100)

def m2p2(vol:int) -> float:
    import math
    exponent = ((vol / 1000.0) + 10)
    numerator = (math.pow(2, exponent) - 1)
    return numerator / 1023.0


def testreal(volf:float):
    return (volf, log2real(real2log(volf)))

def testlog(vol:int):
    return (vol, real2log(log2real(vol)))
