from random import randint

def main():
	#input q and g
	q=int(input("Enter Q(modulus) : "))
	g=int(input("Enter G(base) : "))

	print("\n")
	#find private key for alice and bob
	xa=randint(1,q)
	xb=randint(1,q)
	

	print("private key of alice : {} \n private key of bob : {}".format(xa,xb))
	
	#find public key
	ya=pow(g,xa,q)
	yb=pow(g,xb,q)
	print("\n")
	print("public key of alice : {} \n public key of bob : {}".format(ya,yb))

	#find shared key
	ka=pow(yb,xa,q)
	kb=pow(ya,xb,q)
	print("\n")
	print("shared key of alice : {} \n shared key of bob : {}".format(ka,kb))
	
	
	
if __name__=="__main__":
	main()
