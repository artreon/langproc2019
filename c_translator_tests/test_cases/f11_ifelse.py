def main():
    a=0
    b=0
    if(1<2):
        a = 1
    else:
        a = 2

    if(1>2):
        b = 1
    else:
        b = 2

    return a + b

# Boilerplate
if __name__ == "__main__":
    import sys
    ret=main()
    sys.exit(ret)

