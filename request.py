import requests

k = open("mensagens.txt", "r")
menssage = k.read()
k.close()
print(menssage)
req = requests.get(menssage[:len(menssage)-1])
k = open("mensagens.txt", "w+")
k.write(req.text)
