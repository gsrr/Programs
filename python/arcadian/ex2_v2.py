# Version 2:

# extract_lowest_product : O(n)
# upcharge_color : O(1)
# upcharge_size : O(1)


color_list = []
size_list = []

def extract_product_key(productArr, color_list, size_list):
    if productArr[1] not in color_list:
        color_list.append(productArr[1])
    color_index = str(color_list.index(productArr[1]))
    if productArr[2] not in size_list:
        size_list.append(productArr[2])
    size_index = str(size_list.index(productArr[2]))
 
    return color_index + size_index


def read_input(file_name):
    global color_list
    global size_list
    product_dict = {}
    with open(file_name, "r") as fr:
        lines = fr.readlines()
        for i in range(1, len(lines)):
            product = lines[i].strip()
            if  product == "":
                continue
            product = product.replace(",", "").replace("$", "")
            productArr = product.split()
            product_key = extract_product_key(productArr, color_list, size_list)
            product_dict[product_key] = productArr
    return product_dict


def extract_lowest_product(product_dict):
    key = None
    keys = product_dict.keys()
    lowest_product = product_dict[keys[0]]
    lowest_cost = int(lowest_product[3])
    for i in range(1, len(keys)):
        if int(product_dict[keys[i]][3]) < lowest_cost:
            lowest_product = product_dict[keys[i]]
            lowest_cost = int(lowest_product[3])
            key  = keys[i]

    print "Item:", lowest_product[0].split("-")[0] ,"$" + lowest_product[3] 
    return key


def upcharge_color(key, product_dict):
    print "Color"
    print "\t", product_dict[key][1].upper()
    global color_list
    for i in range(len(color_list)):
        product_key = str(i) + key[1]
        if product_key != key:
            upcharge_cost = int(product_dict[product_key][3]) - int(product_dict[key][3])
            print "\t", product_dict[product_key][1].upper(), "(+$" + str(upcharge_cost) + ")"

    print

def upcharge_size(key, product_dict):
    print "Size"
    print "\t", product_dict[key][2].upper()
    global size_list
    for i in range(len(size_list)):
        product_key = key[0] + str(i)
        if product_key != key:
            upcharge_cost = int(product_dict[product_key][3]) - int(product_dict[key][3])
            print "\t", product_dict[product_key][2].upper(), "(+$" + str(upcharge_cost) + ")"

    print

def main():
    print
    product_dict = read_input("ex2_input")
    key = extract_lowest_product(product_dict)    
    upcharge_color(key, product_dict)
    upcharge_size(key, product_dict)

    

if __name__ == "__main__":
    main()
