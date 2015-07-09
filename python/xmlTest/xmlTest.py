import xml.etree.ElementTree as ET
from random import randint





def country_list(root):
    data = root.findall("./country")
    for item in data:
        print item.tag, item.attrib

def country_rank(root, name):
    data = root.find("./country[@name='%s']/rank"%name)
    print "old rank:", data.text

def set_country_rank(tree, root, name, value):
    print "set rank:%s"%value
    data = root.find("./country[@name='%s']/rank"%name)
    data.text = value
    tree.write("output_rank.xml")

def get_country_name(root, idx):
    data = root.findall("./country")
    print "oldname:" + str(idx) , data[idx].attrib['name']
    return data[idx].attrib['name']


def set_country_name(tree, root, name, newName):
    data = root.find("./country[@name='%s']"%name)
    data.attrib['name'] = newName
    tree.write("output_name.xml")

def swap_country_name(tree, root, name1, name2):
    data1 = root.find("./country[@name='%s']"%name1)
    data2 = root.find("./country[@name='%s']"%name2)
    data1.attrib['name'] = name2
    data2.attrib['name'] = name1
    tree.write("output_name_swap.xml")

def remove_country(tree, root, name):
    data = root.find("./country[@name='%s']"%name)
    root.remove(data)
    tree.write("output_remove.xml")



if __name__ == "__main__":
    tree = ET.parse('test.xml')
    root = tree.getroot()
    country_list(root)
    country_rank(root, "Singapore")
    set_country_rank(tree, root, "Singapore", str(randint(0,9)))
    set_country_name(tree, root, "Singapore", "Taiwan")
    name1 = get_country_name(root, 0)
    name2 = get_country_name(root, 1)
    swap_country_name(tree, root, name1, name2)
    remove_country(tree, root, "Taiwan")
