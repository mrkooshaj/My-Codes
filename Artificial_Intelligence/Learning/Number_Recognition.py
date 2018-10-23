import matplotlib
import sklearn
import sys
import numpy as np
from sklearn.naive_bayes import MultinomialNB
from sklearn import datasets
from matplotlib import pyplot as plt
from sklearn import svm
from sklearn import linear_model
from sklearn.model_selection import GridSearchCV


#read train data from file and store in two dimensional array

filename = "train.txt"
f = open(filename, "r")
A = f.readlines()
f.close()

n = len(A)
m = 65
Array = [[0] * m for i in range(n)]
for i in range(n):
    s = A[i].split(",")
    for j in range(m):
       Array[i][j] = int(s[j])

#end read and store

#show two numbers (part a)

print("This number is ",Array[2][64])

for x in range (0,8):
    for y in range (0,8):
        plt.plot([x,x,x+1,x+1,x],[7-y,8-y,8-y,7-y,7-y],'#000000')
        if (Array[2][y * 8 + x] == 0):
            plt.fill([x,x,x+1,x+1,x],[7-y,8-y,8-y,7-y,7-y],'#FFFFFF')
        if (Array[2][y * 8 + x] == 1):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#F0F0F0')
        if (Array[2][y * 8 + x] == 2):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#E0E0E0')
        if (Array[2][y * 8 + x] == 3):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#D0D0D0')
        if (Array[2][y * 8 + x] == 4):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#C0C0C0')
        if (Array[2][y * 8 + x] == 5):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#B0B0B0')
        if (Array[2][y * 8 + x] == 6):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#A0A0A0')
        if (Array[2][y * 8 + x] == 7):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#909090')
        if (Array[2][y * 8 + x] == 8):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#808080')
        if (Array[2][y * 8 + x] == 9):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#707070')
        if (Array[2][y * 8 + x] == 10):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#606060')
        if (Array[2][y * 8 + x] == 11):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#505050')
        if (Array[2][y * 8 + x] == 12):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#404040')
        if (Array[2][y * 8 + x] == 13):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#303030')
        if (Array[2][y * 8 + x] == 14):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#202020')
        if (Array[2][y * 8 + x] == 15):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#101010')
        if (Array[2][y * 8 + x] == 16):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#000000')

plt.show()

print("This number is ",Array[3][64])


for x in range (0,8):
    for y in range (0,8):
        plt.plot([x,x,x+1,x+1,x],[7-y,8-y,8-y,7-y,7-y],'#000000')
        if (Array[3][y * 8 + x] == 0):
            plt.fill([x,x,x+1,x+1,x],[7-y,8-y,8-y,7-y,7-y],'#FFFFFF')
        if (Array[3][y * 8 + x] == 1):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#F0F0F0')
        if (Array[3][y * 8 + x] == 2):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#E0E0E0')
        if (Array[3][y * 8 + x] == 3):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#D0D0D0')
        if (Array[3][y * 8 + x] == 4):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#C0C0C0')
        if (Array[3][y * 8 + x] == 5):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#B0B0B0')
        if (Array[3][y * 8 + x] == 6):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#A0A0A0')
        if (Array[3][y * 8 + x] == 7):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#909090')
        if (Array[3][y * 8 + x] == 8):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#808080')
        if (Array[3][y * 8 + x] == 9):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#707070')
        if (Array[3][y * 8 + x] == 10):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#606060')
        if (Array[3][y * 8 + x] == 11):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#505050')
        if (Array[3][y * 8 + x] == 12):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#404040')
        if (Array[3][y * 8 + x] == 13):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#303030')
        if (Array[3][y * 8 + x] == 14):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#202020')
        if (Array[3][y * 8 + x] == 15):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#101010')
        if (Array[3][y * 8 + x] == 16):
            plt.fill([x, x, x + 1, x + 1,x], [7 - y, 8 - y, 8 - y, 7 - y,7-y], '#000000')

plt.show()


#end of part (a)

#opening test data file and separating arrays

m = 64
Array1 = [[0] * m for i in range(n)]
for i in range(n):
    for j in range(m):
       Array1[i][j] = Array[i][j]

Array2 = [0] * n
for i in range(n):
    Array2[i] = Array[i][64]

filename = "test.txt"
f = open(filename, "r")
A = f.readlines()
f.close()

n = len(A)
m = 65
Test = [[0] * m for i in range(n)]
for i in range(n):
    s = A[i].split(",")
    for j in range(m):
       Test[i][j] = int(s[j])

m = 64
Test1 = [[0] * m for i in range(n)]
for i in range(n):
    for j in range(m):
       Test1[i][j] = Test[i][j]

Test2 = [0] * n
for i in range(n):
    Test2[i] = Test[i][64]

#end of seperation and file read

#start of part b)

classifier = MultinomialNB()
classifier.fit(Array1,Array2)
prediction_naive_bayes = classifier.predict(Test1)
naive_bayes_score = classifier.score(Test1,Test2)
print("Naive Bayes Score :" ,naive_bayes_score)

classifier = svm.LinearSVC()
classifier.fit(Array1,Array2)
prediction_svm_linear = classifier.predict(Test1)
svm_linear_score = classifier.score(Test1,Test2)
print("SVM Score: ", svm_linear_score)

classifier = linear_model.LogisticRegression()
classifier.fit(Array1,Array2)
prediction_logistic_regression = classifier.predict(Test1)
logistic_regression_score = classifier.score(Test1,Test2)
print("Logistic Regression Score: ", logistic_regression_score)

#end of part b)

#part c in the doc!

#start of part d)

filename = "train.txt"
f = open(filename, "r")
A = f.readlines()
f.close()

n = len(A)
m = 65
Train = [[0] * m for i in range(n)]
for i in range(n):
    s = A[i].split(",")
    for j in range(m):
       Train[i][j] = int(s[j])

m = 64
Train1 = [[0] * m for i in range(n)]
for i in range(n):
    for j in range(m):
       Train1[i][j] = Array[i][j]

Train2 = [0] * n
for i in range(n):
    Train2[i] = Train[i][64]


parameterc = {"C": [1,2,5,10]}

classifier = GridSearchCV(estimator=svm.LinearSVC(),param_grid=parameterc,cv=5)
classifier.fit(Train1,Train2)
prediction_svm_linear = classifier.predict(Test1)
svm_linear_score = classifier.score(Test1,Test2)
print("Best SVM Parameter :" , classifier.best_params_)
print("SVM New Score :" , svm_linear_score)

parameterc = {"C": [1,2,5,10]}
classifier = GridSearchCV(estimator=linear_model.LogisticRegression(),param_grid=parameterc,cv=5)
classifier.fit(Train1,Train2)
prediction_logistic_regression = classifier.predict(Test1)
logistic_regression_score = classifier.score(Test1,Test2)
print("Best Logistic Parameter:" , classifier.best_params_)
print("Logistic New Score :" ,logistic_regression_score)

parameteralpha = {"alpha": [0.001,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9]}
classifier = GridSearchCV(estimator=MultinomialNB(),param_grid=parameteralpha,cv=5)
classifier.fit(Train1,Train2)
prediction_naive_bayes = classifier.predict(Test1)
naive_bayes_score = classifier.score(Test1,Test2)
print("Naive Bayes Best Parameter :" , classifier.best_params_)
print("Naive Bayes New Score :" , naive_bayes_score)

#end of part d)


#start of part e)

counter = 0;

for i in range(0,n):
    if (prediction_logistic_regression[i] != Test2[i]):
        print("this number is predicted",prediction_logistic_regression[i] ,"While it is",Test2[i])
        for x in range(0, 8):
            for y in range(0, 8):
                plt.plot([x, x, x + 1, x + 1, x], [7 - y, 8 - y, 8 - y, 7 - y, 7 - y], '#000000')
                if (Test[i][y * 8 + x] == 0):
                    plt.fill([x, x, x + 1, x + 1, x], [7 - y, 8 - y, 8 - y, 7 - y, 7 - y], '#FFFFFF')
                if (Test[i][y * 8 + x] == 1):
                    plt.fill([x, x, x + 1, x + 1, x], [7 - y, 8 - y, 8 - y, 7 - y, 7 - y], '#F0F0F0')
                if (Test[i][y * 8 + x] == 2):
                    plt.fill([x, x, x + 1, x + 1, x], [7 - y, 8 - y, 8 - y, 7 - y, 7 - y], '#E0E0E0')
                if (Test[i][y * 8 + x] == 3):
                    plt.fill([x, x, x + 1, x + 1, x], [7 - y, 8 - y, 8 - y, 7 - y, 7 - y], '#D0D0D0')
                if (Test[i][y * 8 + x] == 4):
                    plt.fill([x, x, x + 1, x + 1, x], [7 - y, 8 - y, 8 - y, 7 - y, 7 - y], '#C0C0C0')
                if (Test[i][y * 8 + x] == 5):
                    plt.fill([x, x, x + 1, x + 1, x], [7 - y, 8 - y, 8 - y, 7 - y, 7 - y], '#B0B0B0')
                if (Test[i][y * 8 + x] == 6):
                    plt.fill([x, x, x + 1, x + 1, x], [7 - y, 8 - y, 8 - y, 7 - y, 7 - y], '#A0A0A0')
                if (Test[i][y * 8 + x] == 7):
                    plt.fill([x, x, x + 1, x + 1, x], [7 - y, 8 - y, 8 - y, 7 - y, 7 - y], '#909090')
                if (Test[i][y * 8 + x] == 8):
                    plt.fill([x, x, x + 1, x + 1, x], [7 - y, 8 - y, 8 - y, 7 - y, 7 - y], '#808080')
                if (Test[i][y * 8 + x] == 9):
                    plt.fill([x, x, x + 1, x + 1, x], [7 - y, 8 - y, 8 - y, 7 - y, 7 - y], '#707070')
                if (Test[i][y * 8 + x] == 10):
                    plt.fill([x, x, x + 1, x + 1, x], [7 - y, 8 - y, 8 - y, 7 - y, 7 - y], '#606060')
                if (Test[i][y * 8 + x] == 11):
                    plt.fill([x, x, x + 1, x + 1, x], [7 - y, 8 - y, 8 - y, 7 - y, 7 - y], '#505050')
                if (Test[i][y * 8 + x] == 12):
                    plt.fill([x, x, x + 1, x + 1, x], [7 - y, 8 - y, 8 - y, 7 - y, 7 - y], '#404040')
                if (Test[i][y * 8 + x] == 13):
                    plt.fill([x, x, x + 1, x + 1, x], [7 - y, 8 - y, 8 - y, 7 - y, 7 - y], '#303030')
                if (Test[i][y * 8 + x] == 14):
                    plt.fill([x, x, x + 1, x + 1, x], [7 - y, 8 - y, 8 - y, 7 - y, 7 - y], '#202020')
                if (Test[i][y * 8 + x] == 15):
                    plt.fill([x, x, x + 1, x + 1, x], [7 - y, 8 - y, 8 - y, 7 - y, 7 - y], '#101010')
                if (Test[i][y * 8 + x] == 16):
                    plt.fill([x, x, x + 1, x + 1, x], [7 - y, 8 - y, 8 - y, 7 - y, 7 - y], '#000000')

        plt.show()

        counter = counter + 1;
        if (counter == 2):
            break

#end of part e)










