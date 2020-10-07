def isNumber(x):
    try:
        float(x)
        return True
    except ValueError:
        return False

inp = ' '
stack = []
result = []
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
                body = [i, second]
                stack.append(' '.join(map(str,body)))
            elif (i in operator[-4:20]):
                j = -1
                stackLen = len(stack)
                while (len(str(stack[j])) != 1 or not(stack[j] >= 'A' and stack[j] <= 'Z')):
                    j -= 1
                second = stack.pop(j)
                third = stack.pop(j + 1)
                body = [i, second, third]
                stack.insert(j + 1, ' '.join(map(str,body)))
            elif (i in operator[3:16]):
                a = str(stack.pop())
                b = str(stack.pop())
                
                body = [b, i, a]
                stack.append(' '.join(map(str,body)))
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
    strong = ' '.join(map(str, stack))
    print(strong)
    stack.clear()
