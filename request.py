import requests

k = open("mensagens.txt", "r")
menssage = k.read()
print(menssage)
req = requests.get()
print(req.text)
