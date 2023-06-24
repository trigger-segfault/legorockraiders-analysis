
def findfrac(frac, maxcount=4096, allowed_error=100000):
    n = d = 1
    allowed_error = frac / allowed_error
    value = n / d
    #
    while abs(value - frac) > allowed_error:
        maxcount -= 1
        if maxcount <= 0:
            return 'maxcount reached'
        if value < frac:
            n += 1
        elif value > frac:
            d += 1
        value = n / d
    return f'{n} / {d}'


findfrac(0.04) # 1 / STANDARD_FRAMERATE
