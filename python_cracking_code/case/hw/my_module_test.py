from my_module import e_repr, e_eval, set_key

# Test string

set_key(1)
x = 'abc2389ZBD'
x_repr = e_repr(x)

assert x_repr == "'bcd3490aCE'" , 'string to e_string failed'

x_eval = e_eval(x_repr)

assert x_eval == x , 'e_string to string failed'

print 'string: passed.'

# Test int

set_key(5)
x1 = 1357
x2 = -529
x1_repr = e_repr(x1)
x2_repr = e_repr(x2)

assert x1_repr == '6802' and x2_repr == '-074', 'int to e_string failed'

x1_eval = e_eval(x1_repr)
x2_eval = e_eval(x2_repr)

assert x1_eval == x1 and x2_eval == x2, 'e_string to int failed'

print 'int: passed'

# Test float
set_key(257)

x1 = 1.25
x2 = -0.3
x1_repr = e_repr(x1)
x2_repr = e_repr(x2)

assert x1_repr == '8.92' and x2_repr == '-7.0', 'float to e_string failed'

x1_eval = e_eval(x1_repr)
x2_eval = e_eval(x2_repr)

assert x1_eval == x1 and x2_eval == x2 , 'e_string to float failed'

print 'float: passed'

# Test list and tuple
set_key(0)

x1 = [12,34]
x2 = ['ab','cd']
x1_repr = e_repr(x1)
x2_repr = e_repr(x2)

assert x1_repr == '(12,34)' and x2_repr == "('ab','cd')", 'list to e_string failed'

x1_eval = e_eval(x1_repr)
x2_eval = e_eval(x2_repr)

assert x1_eval == x1 and x2_eval == x2 , 'e_string to list failed'

set_key(13)

x1 = ('ab',34.25)
x2 = ('-12','cd')
x1_repr = e_repr(x1)
x2_repr = e_repr(x2)

assert x1_repr == "['no',67.58]" and x2_repr == "['-45','pq']", 'tuple to e_string failed'

x1_eval = e_eval(x1_repr)
x2_eval = e_eval(x2_repr)

assert x1_eval == x1 and x2_eval == x2 , 'e_string to tuple failed'

print 'list and tuple: passed'

# Test dict # sorted by key in e_repr
set_key(259)

x1 = {2:'two',1:'one'}
x2 = {12:34, 56:'78'}
x1_repr = e_repr(x1)
x2_repr = e_repr(x2)

assert x1_repr == "{0:'nmd',1:'svn'}" and x2_repr == "{01:23,45:'67'}", 'dict to e_string failed'

x1_eval = e_eval(x1_repr)
x2_eval = e_eval(x2_repr)

assert x1_eval == x1 and x2_eval == x2 , 'e_string to dict failed'

print 'dict: passed'
