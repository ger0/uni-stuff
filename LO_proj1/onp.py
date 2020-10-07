def isNumber(x):
    try:
        float(x)
        return True
    except ValueError:
        return False

inp = ' '
stack = []
operator = ['NOT', '~', '¬']
operator += ['AND', '&', '∧']
operator += ['OR', '|', '∨']
operator += ['IMPLIES', '→']
operator += ['IFF', '↔']
operator += ['XOR', '⊕']
operator += ['FORALL', '∀']
operator += ['EXISTS', '∃']

while inp[0] != "exit":
    inp = list(map(str,input().split()))
    for i in inp:
        if (i in operator):
            if (i in operator[0:3]): 
                second = str(stack.pop())
                body = ['(', i, second, ')']
                stack.append(''.join(map(str,body)))
            elif (i in operator[-4:20]):
                third = stack.pop()
                second = stack.pop()
                body = [i, second, third]
                tempBody = ['(', ' '.join(map(str, body)), ')']
                stack.insert(j + 1, ''.join(map(str, tempBody)))
            elif (i in operator[3:16]):
                a = str(stack.pop())
                b = str(stack.pop())
                
                body = [b, i, a]
                tempBody = ['(', ' '.join(map(str, body)), ')']
                stack.append(''.join(map(str, tempBody)))
        elif ((i[0] >= 'f' and i[0] <= 'n') or (i[0] >= 'p' and i[0] <= 'z')):
            name, arg = i.split('/')
            body = [i[0],'(']
            li = []
            for j in range(int(arg)):
                li.append(str(stack.pop()))
                if (j != int(arg) - 1):
                        li.append(', ')
            li.reverse()
            body.append(''.join(map(str,li)))
            body.append(')')
            stack.append(''.join(map(str, body)))
        elif ((i >= 'A' and i <= 'Z') or (i >= 'a' and i <= 'e')):
            stack.append(i)
    print(' '.join(map(str, stack)))
    stack.clear()
