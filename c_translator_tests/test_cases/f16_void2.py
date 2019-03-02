def voidF(x,y,z):
    a = x+y+z*x*y

def main():
    voidF(1,3,4)
    return 12

# Boilerplate
if __name__ == "__main__":
    import sys
    ret=main()
    sys.exit(ret)

