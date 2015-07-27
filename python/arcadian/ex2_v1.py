# Version 1:

# extract_lowest_product : O(n)
# upcharge_color : O(n)
# upcharge_size : O(n)




def read_input(file_name):
    product_list = []
    with open(file_name, "r") as fr:
        lines = fr.readlines()
        for i in range(1, len(lines)):
            line = lines[i].strip()
            if line == "":
                continue
            line = line.replace(",", "").replace("$", "")
            product_list.append(line.split())

    return product_list


def extract_lowest_product(product_list):
    lowest_product = product_list[0]
    lowest_cost = int(lowest_product[3])
    for i in range(1, len(product_list)):
        if int(product_list[i][3]) < lowest_cost:
            lowest_product = product_list[i]
            lowest_cost = int(lowest_product[3])

    print "Item:", lowest_product[0].split("-")[0] ,"$" + lowest_product[3] 
    return lowest_product


def upcharge_color(lowest_product, product_list):
    print "Color"
    print "\t", lowest_product[1].upper()
    for product in product_list:
        if product[2] == lowest_product[2]: # size is equal
            if product[1] != lowest_product[1]: # color is not equal
                upcharge_cost = int(product[3]) - int(lowest_product[3])
                print "\t", product[1].upper(), "(+$" + str(upcharge_cost) + ")"

    print

def upcharge_size(lowest_product, product_list):
    print "SIZE"
    print "\t", lowest_product[2].upper()
    for product in product_list:
        if product[1] == lowest_product[1]: # color is equal
            if product[2] != lowest_product[2]: # size is not equal
                upcharge_cost = int(product[3]) - int(lowest_product[3])
                print "\t", product[2].upper(), "(+$" + str(upcharge_cost) + ")"

    print

def main():
    print
    product_list = read_input("ex2_input")
    lowest_product = extract_lowest_product(product_list)    
    upcharge_color(lowest_product, product_list)
    upcharge_size(lowest_product, product_list)

    

if __name__ == "__main__":
    main()
