import random

f_data = open('data.txt', 'w')
f_answer = open('answers.txt', 'w')

n = random.randint(2, 3)

a = [0] * n
for i in range(n):
    a[i] = [0] * n
    
det = 1
    
for i in range(n):
    a[i][i] = random.randint(1, 10)
    det *= a[i][i]
    
 
for i in range(10):
    row1 = random.randint(0, n - 1)
    row2 = random.randint(0, n - 1)
     
    while(row2 == row1):
        row2 = random.randint(0, n - 1)
    
    for j in range(n):
        a[row1][j] += a[row2][j]   
 
for i in range(10):
    col1 = random.randint(0, n - 1)
    col2 = random.randint(0, n - 1)
    
    while(col2 == col1):
        col2 = random.randint(0, n - 1)


    
    for j in range(n):
        a[j][col1] += a[j][col2]
        
 
f_data.write(str(n) + '\n')
for i in range(n):
    for j in range(n):
        f_data.write(str(a[i][j]) + ' ')
    f_data.write('\n')



f_answer.write(str(det) + '\n') 

print(n)
for i in range(n):
    for j in range(n):
        print(a[i][j], end = ' ')
    print('')

print(det)

f_data.close()
f_answer.close()