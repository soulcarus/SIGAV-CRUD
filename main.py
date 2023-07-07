from flask import Flask, render_template, request, redirect, session
import subprocess

app = Flask(__name__)
app.secret_key = 'chave_secreta'

def alt(num):
    eventos = []
    arquivo = open('./arquivos/eventos.txt', 'r')

    for linha in arquivo:
        evento_data = linha.split()
        evento = {
            'nome': evento_data[0],
            'data': evento_data[1],
            'capacidade': int(evento_data[2]),
            'valor': float(evento_data[3]),
            'local': evento_data[4]
        }
        eventos.append(evento)
    arquivo.close()

    arquivo = open('eventos.txt', 'w')

    count = 1

    for user in eventos:
        if int(num) != count:
            arquivo.writelines(f"{user['nome']} {user['data']} {user['capacidade']} {user['valor']} {user['local']}\n")
        else:
            arquivo.writelines(f"{user['nome']} {user['data']} {user['capacidade'] - 1} {user['valor']} {user['local']}\n")
        count += 1

def ler_eventos():
    eventos = []
    arquivo = open('./arquivos/eventos.txt', 'r')

    for linha in arquivo:
        evento_data = linha.split()
        evento = {
            'nome': evento_data[0],
            'data': evento_data[1],
            'capacidade': int(evento_data[2]),
            'valor': float(evento_data[3]),
            'local': evento_data[4]
        }
        eventos.append(evento)

    return eventos

def ler_usuarios():
    usuarios = []
    arquivo = open('./arquivos/usuarios.txt', 'r')

    for linha in arquivo:
        usuarios_data = linha.split()
        evento = {
            'nome': usuarios_data[2],
            'login': usuarios_data[0],
            'senha': usuarios_data[1],
            'email': usuarios_data[3],
            'telefone': usuarios_data[4]
        }
        usuarios.append(evento)

    return usuarios

def ler_evento_usuario(login):
    eventos_usuario = []
    
    # Abra o arquivo de eventos do usuário para leitura
    with open("./arquivos/eventos_usuario.txt", "r") as file:
        # Leia cada linha do arquivo
        for linha in file:
            # Extraia o login e o número do evento da linha
            login_lido, num_evento = linha.split()
            # Verifique se o login lido corresponde ao login fornecido
            if login_lido == login:
                # Encontre o evento correspondente na lista de eventos
                eventos = ler_eventos()
                evento_usuario = eventos[int(num_evento) - 1]
                eventos_usuario.append(evento_usuario)
    
    return eventos_usuario

@app.route('/')
def start():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def login():

    eventos = ler_eventos()
    usuarios = ler_usuarios()

    login = request.form['login']
    senha = request.form['senha']

    session['login'] = login
    session['senha'] = senha

    for usuario in usuarios:
        if usuario['login'] == login and usuario['senha'] == senha:

            subprocess.Popen(['./script', 'login', login, senha]).communicate()

            return render_template('eventos.html', eventos=eventos, usuario=usuario)
    
    return('login inválido')

@app.route('/cadastro', methods=['POST'])
def cadastro():
    return render_template('cadastro.html')

@app.route('/cadastrar', methods=['POST'])
def cadastrar():
    nome = request.form['nome']
    email = request.form['email']
    telefone = request.form['telefone']
    login = request.form['login']
    senha = request.form['senha']

    usuarios = ler_usuarios()
    for usuario in usuarios:
        if login == usuario['login']:
            return 'usuario existente'
    
    subprocess.Popen(['./script', 'cadastrar', login, senha, nome, email, telefone]).communicate()
    return redirect('/')


@app.route('/index', methods=['POST'])
def index():
    eventos = ler_eventos()
    
    return render_template('index.html', eventos=eventos)

@app.route('/participar', methods=['POST'])
def participar():
    num_evento = request.form['num_evento']
    login = session.get('login')
    senha = session.get('senha')

    eventos = ler_eventos()
    evento = eventos[int(num_evento) - 1]
    evento['capacidade'] -= 1
    
    alt(num_evento)
    
    # Chame a função adicionar_evento_usuario aqui
    subprocess.Popen(['./script', 'participar', login, num_evento]).communicate()

    return 'cadastrado no evento!'

@app.route('/meu_evento', methods=['POST'])
def meu_evento():
    login = session.get('login')
    eventos = ler_evento_usuario(login)
    
    if eventos:
        return render_template('user_event.html', eventos=eventos)
    else:
        return 'Você não está cadastrado em nenhum evento'

@app.route('/adicionar', methods=['POST'])
def adicionar():
    nome = request.form['nome']
    data = request.form['data']
    capacidade = request.form['capacidade']
    valor = request.form['valor']
    local = request.form['local']

    subprocess.Popen(['./script', 'adicionar', nome, data, capacidade, valor, local]).communicate()

    eventos = ler_eventos()
    
    return render_template('index.html', eventos=eventos)

@app.route('/editar', methods=['POST'])
def editar():
    num_evento = request.form['num_evento']
    session['num_evento'] = num_evento
    eventos = ler_eventos()
    evento = eventos[int(num_evento) - 1]  # Obter o evento selecionado com base no índice
    return render_template('editar.html', evento=evento)

@app.route('/atualizar', methods=['POST'])
def atualizar():
    num_evento = session.get('num_evento')
    nome = request.form['nome']
    data = request.form['data']
    capacidade = request.form['capacidade']
    valor = request.form['valor']
    local = request.form['local']

    subprocess.Popen(['./script', 'editar', num_evento, nome, data, capacidade, valor, local]).communicate()

    eventos = ler_eventos()
    
    return render_template('index.html', eventos=eventos)

@app.route('/remover', methods=['POST'])
def remover():
    num_evento = request.form['num_evento']

    
    
    eventos = ler_eventos()

    subprocess.Popen(['./script', 'remover', num_evento]).communicate()
    
    eventos = ler_eventos()
    
    return render_template('index.html', eventos=eventos)

if __name__ == '__main__':
    app.run(port=8000)
