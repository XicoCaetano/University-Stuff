#Trabalho realizado por Francisco Caetano e Tiago Mendes (TP2)
import time
import random
import functools
import turtle
import math

MAX_X = 600
MAX_Y = 800
DEFAULT_SIZE = 20
SNAKE_SHAPE = 'square'
HIGH_SCORES_FILE_PATH = 'high_scores.txt'
# Controla a velocidade da cobra. Quanto menor o valor, mais rápido é o movimento da cobra.
SPEED = 0.2

apple = turtle.Turtle()
apple.ht()
apple.pu()
golden = turtle.Turtle()
golden.ht()
golden.pu()
burger = turtle.Turtle()
burger.ht()
burger.pu()
peach = turtle.Turtle()
peach.ht()
peach.pu()

def load_high_score(state):
    # se já existir um high score devem guardar o valor em state['high_score']
    file = open('high_scores.txt','r')
    recorde = file.readlines()
    recorde = int(recorde[0])
    file.close()
    state['high_score'] = recorde

def write_high_score_to_file(state):
    # devem escrever o valor que está em state['high_score'] no ficheiro de high scores
    file = open('high_scores.txt','w')
    texto = state['score']
    texto = str(texto)
    file.write(texto)
    file.close()

def create_score_board(state):
    score_board = turtle.Turtle()
    score_board.speed(0)
    score_board.shape("square")
    score_board.color("black")
    score_board.penup()
    score_board.hideturtle()
    score_board.goto(0, MAX_Y / 2.2)
    state['score_board'] = score_board
    load_high_score(state)
    update_score_board(state)

def update_score_board(state):
    state['score_board'].clear()
    state['score_board'].write("Score: {} High Score: {}".format(state['score'], state['high_score']), align="center", font=('Helvetica', 24, "normal"))

def go_up(state):
    if state['snake']['current_direction'] != 'down':
        state['snake']['current_direction'] = 'up'

def go_down(state):
    if state['snake']['current_direction'] != 'up':
        state['snake']['current_direction'] = 'down'

def go_left(state):
    if state['snake']['current_direction'] != 'right':
        state['snake']['current_direction'] = 'left'

def go_right(state):
    if state['snake']['current_direction'] != 'left':
        state['snake']['current_direction'] = 'right'

def init_state():
    state = {}
    # Informação necessária para a criação do score board
    state['score_board'] = None
    state['new_high_score'] = False
    state['high_score'] = load_high_score(state)
    state['score'] = 0
    # Para gerar a comida deverá criar um nova tartaruga e colocar a mesma numa posição aleatória do campo
    state['food'] = {'apple':[999, 999], 'golden':[999, 999, 0], 'burger':[999, 999, 0], 'peach':[999, 999, 0]}
    state['window'] = None
    snake = {
        'head': None,                  # Variável que corresponde à cabeça da cobra
        'current_direction': None,     # Indicação da direcção atual do movimento da cobra
        'body':[[0,0,0]],
        'turtles': []
    }
    state['snake'] = snake
    return state

def setup(state):
    window = turtle.Screen()
    window.setup(width=MAX_X, height=MAX_Y)
    
    window.bgpic('bg.png')
    window.addshape('apple.gif')
    window.addshape('golden.gif')
    window.addshape('burger.gif')
    window.addshape('peach.gif')
    window.addshape('headdown.gif')
    window.addshape('headup.gif')
    window.addshape('headleft.gif')
    window.addshape('headright.gif')
    window.addshape('youlost.gif')
    
    window.listen()
    window.onkey(functools.partial(go_up, state), 'w')
    window.onkey(functools.partial(go_down, state), 's')
    window.onkey(functools.partial(go_left, state), 'a')
    window.onkey(functools.partial(go_right, state), 'd')
    window.tracer(0)
    
    apple.shape('apple.gif')
    golden.shape('golden.gif')
    golden.goto(999, 999)
    burger.shape('burger.gif')
    burger.goto(999, 999)
    peach.shape('peach.gif')
    peach.goto(999, 999)
    
    state['window'] = window
    snake = state['snake']
    snake['current_direction'] = 'stop'
    snake['head'] = turtle.Turtle()
    snake['head'].shape(SNAKE_SHAPE)
    snake['head'].showturtle()
    snake['head'].pu()
    
    snake['head'].shape('headdown.gif')
    
    snake['head'].color('#CCCCCC')
    create_score_board(state)
    create_food(state)

def move(state):
    ''' 
    Função responsável pelo movimento da cobra no ambiente.
    '''
    snake = state['snake']
    body = snake['body']
    tamanho = len(snake['turtles']) + 1
    #mexer corpo
    if tamanho > 1:
        for z in range(1, tamanho): #atualizar lista
            body[-z][0] = body[-z - 1][0] #atualizar x
            body[-z][1] = body[-z - 1][1] #atualizar y
            body[-z][2] = body[-z - 1][2] #atualizar direção                
            snake['turtles'][-z].goto(body[-z][0], body[-z][1])
    #mexe a cabeça
    if snake['current_direction'] == 'up':
        body[0][1] = body[0][1] + 20
        body[0][2] = 'up'
        snake['head'].shape('headup.gif')
    elif snake['current_direction'] == 'down':
        body[0][1] = body[0][1] - 20
        body[0][2] = 'down'
        snake['head'].shape('headdown.gif')
    elif state['snake']['current_direction'] == 'left':
        body[0][0] = body[0][0] - 20
        body[0][2] = 'left'
        snake['head'].shape('headleft.gif')
    elif snake['current_direction'] == 'right':
        body[0][0] = body[0][0] + 20
        body[0][2] = 'right'
        snake['head'].shape('headright.gif')
    snake['head'].goto(snake['body'][0][0],snake['body'][0][1])
        
def create_food(state):
    ''' 
        Função responsável pela criação da comida. Note que elas deverão ser colocadas em posições aleatórias, mas dentro dos limites do ambiente.
    '''
    create_apple(state)
    chancegolden = random.randrange(1,5)
    if chancegolden == 1 and state['food']['golden'][0] == 999 and state['food']['golden'][1] == 999:
        create_golden(state)
    chanceburger = random.randrange(1,5)
    if chanceburger == 1 and state['food']['burger'][0] == 999 and state['food']['burger'][1] == 999:
        create_burger(state)
    comprimento = len(state['snake']['body'])
    if comprimento >= 4:
        chancepeach = random.randrange(1,4)
        if chancepeach == 1 and state['food']['peach'][0] == 999 and state['food']['peach'][1] == 999:
            create_peach(state)
        
def create_apple(state):
    cabeça = state['snake']['body'][0]
    applex = random.randrange(-280,281)
    while applex >= cabeça[0] - 10 and applex <= cabeça[0] + 10:
        applex = random.randrange(-280,281)
    appley = random.randrange(-380,281)
    while appley >= cabeça[1] - 10 and appley <= cabeça[1] + 10:
        appley = random.randrange(-380,281)
    apple.goto(applex, appley)
    apple.st()
    # a informação sobre a comida deve ser guardada em state['food']
    state['food']['apple'] = [applex, appley]
    
def create_golden(state):
    cabeça = state['snake']['body'][0]
    goldenx = random.randrange(-280,281)
    while goldenx >= cabeça[0] - 10 and goldenx <= cabeça[0] + 10:
        goldenx = random.randrange(-280,281)
    goldeny = random.randrange(-380,281)
    while goldeny >= cabeça[1] - 10 and goldeny <= cabeça[1] + 10:
        goldeny = random.randrange(-380,281)
    golden.goto(goldenx, goldeny)
    golden.st()
    # a informação sobre a comida deve ser guardada em state['food']
    state['food']['golden'][2] = time.time()
    state['food']['golden'][0] = goldenx
    state['food']['golden'][1] = goldeny
    
def create_burger(state):
    cabeça = state['snake']['body'][0]
    burgerx = random.randrange(-285,286)
    while burgerx >= cabeça[0] - 10 and burgerx <= cabeça[0] + 10:
        burgerx = random.randrange(-285,286)
    burgery = random.randrange(-385,286)
    while burgery >= cabeça[1] - 10 and burgery <= cabeça[1] + 10:
        burgery = random.randrange(-385,286)
    burger.goto(burgerx, burgery)
    burger.st()
    # a informação sobre a comida deve ser guardada em state['food']
    state['food']['burger'][2] = time.time()
    state['food']['burger'][0] = burgerx
    state['food']['burger'][1] = burgery
    
def create_peach(state):
    cabeça = state['snake']['body'][0]
    peachx = random.randrange(-280,281)
    while peachx >= cabeça[0] - 10 and peachx <= cabeça[0] + 10:
        peachx = random.randrange(-280,281)
    peachy = random.randrange(-380,281)
    while peachy >= cabeça[1] - 10 and peachy <= cabeça[1] + 10:
        peachy = random.randrange(-380,281)
    peach.goto(peachx, peachy)
    peach.st()
    # a informação sobre a comida deve ser guardada em state['food']
    state['food']['peach'][2] = time.time()
    state['food']['peach'][0] = peachx
    state['food']['peach'][1] = peachy

def check_if_food_to_eat(state):
    food = state['food']
    ''' 
        Função responsável por verificar se a cobra tem uma peça de comida para comer. Deverá considerar que se a comida estiver a uma distância inferior a 15 pixels a cobra pode comer a peça de comida. 
    '''
    cordshead = state['snake']['body'][0]
    xhead = cordshead[0]
    yhead = cordshead[1]
    #apple
    applex = food['apple'][0]
    appley = food['apple'][1]
    dist_apple = math.sqrt( (applex - xhead)**2 + (appley - yhead)**2 ) #distância entre 2 pontos no plano
    if dist_apple <= 15:
        apple.ht()
        state['score'] += 10
        body = state['snake']['body']
        direction = body[-1][2]
        if direction == 'up':
            body.append([body[-1][0], body[-1][1] - 20, body[-1][2]])
        if direction == 'down':
            body.append([body[-1][0], body[-1][1] + 20, body[-1][2]])
        if direction == 'left':
            body.append([body[-1][0] + 20, body[-1][1], body[-1][2]])
        if direction == 'right':
            body.append([body[-1][0] - 20, body[-1][1], body[-1][2]])
        t = turtle.Turtle()
        t.shape(SNAKE_SHAPE)
        t.color('#7F7F7F')
        t.pu()
        t.goto(body[-1][0], body[-1][1])
        state['snake']['turtles'].append(t)
        if state['score'] > state['high_score']:
            state['high_score'] = state['score']
        update_score_board(state)
        create_food(state)
    
    #golden
    if food['golden'][0] <= 300 and food['golden'][1] <= 400:
        goldenx = food['golden'][0]
        goldeny = food['golden'][1]
        dist_golden = math.sqrt( (goldenx - xhead)**2 + (goldeny - yhead)**2 ) #distância entre 2 pontos no plano
        if dist_golden <= 15:
            golden.ht()
            golden.goto(999,999)
            state['food']['golden'][0] = 999
            state['food']['golden'][1] = 999
            state['score'] += 25
            body = state['snake']['body']
            direction = body[-1][2]
            if direction == 'up':
                body.append([body[-1][0], body[-1][1] - 20, body[-1][2]])
            if direction == 'down':
                body.append([body[-1][0], body[-1][1] + 20, body[-1][2]])
            if direction == 'left':
                body.append([body[-1][0] + 20, body[-1][1], body[-1][2]])
            if direction == 'right':
                body.append([body[-1][0] - 20, body[-1][1], body[-1][2]])
            t = turtle.Turtle()
            t.shape(SNAKE_SHAPE)
            t.color('#7F7F7F')
            t.pu()
            t.goto(body[-1][0], body[-1][1])
            state['snake']['turtles'].append(t)
            if state['score'] > state['high_score']:
                state['high_score'] = state['score']
            update_score_board(state)
        if time.time() >= state['food']['golden'][2] + random.randrange(4,7):
            golden.ht()
            golden.goto(999,999)
            state['food']['golden'][0] = 999
            state['food']['golden'][1] = 999
    
    #burger
    if food['burger'][0] <= 300 and food['burger'][1] <= 400:
        burgerx = food['burger'][0]
        burgery = food['burger'][1]
        dist_burger = math.sqrt( (burgerx - xhead)**2 + (burgery - yhead)**2 ) #distância entre 2 pontos no plano
        if dist_burger <= 15:
            burger.ht()
            burger.goto(999,999)
            state['food']['burger'][0] = 999
            state['food']['burger'][1] = 999
            state['score'] = state['score'] - 50
            body = state['snake']['body']
            direction = body[-1][2]
            if direction == 'up':
                for n in range(3):
                    body.append([body[-1][0], body[-1][1] - 20, body[-1][2]])
            if direction == 'down':
                for n in range(3):
                    body.append([body[-1][0], body[-1][1] + 20, body[-1][2]])
            if direction == 'left':
                for n in range(3):
                    body.append([body[-1][0] + 20, body[-1][1], body[-1][2]])
            if direction == 'right':
                for n in range(3):
                    body.append([body[-1][0] - 20, body[-1][1], body[-1][2]])
            for m in range(3):
                t = turtle.Turtle()
                t.shape(SNAKE_SHAPE)
                t.color('#7F7F7F')
                t.pu()
                t.goto(body[-1][0], body[-1][1])
                state['snake']['turtles'].append(t)
            if state['score'] > state['high_score']:
                state['high_score'] = state['score']
            update_score_board(state)
        if time.time() >= state['food']['burger'][2] + 5:
            burger.ht()
            burger.goto(999,999)
            state['food']['burger'][0] = 999
            state['food']['burger'][1] = 999
    
    #peach
    if food['peach'][0] <= 300 and food['peach'][1] <= 400:
        peachx = food['peach'][0]
        peachy = food['peach'][1]
        snake = state['snake']
        dist_peach = math.sqrt( (peachx - xhead)**2 + (peachy - yhead)**2 ) #distância entre 2 pontos no plano
        if dist_peach <= 15:
            peach.ht()
            peach.goto(999,999)
            state['food']['peach'][0] = 999
            state['food']['peach'][1] = 999
            state['score'] += 20
            body = state['snake']['body']
            comprimento = len(body)
            for d in range(1,4):
                snake['turtles'][-d].ht()
                snake['turtles'][-d].goto(-999,-999)
            snake['turtles'] = snake['turtles'][:-3]
            state['snake']['body'] = state['snake']['body'][:-3]
            if state['score'] > state['high_score']:
                state['high_score'] = state['score']
            update_score_board(state)
        if time.time() >= state['food']['peach'][2] + random.randrange(4,7):
            peach.ht()
            peach.goto(999,999)
            state['food']['peach'][0] = 999
            state['food']['peach'][1] = 999        
        
    # para ler ou escrever os valores de high score, score e new high score, devem usar os respetivos campos do state: state['high_score'], state['score'] e state['new_high_score']

def boundaries_collision(state):
    ''' 
        Função responsável por verificar se a cobra colidiu com os limites do ambiente. Sempre que isto acontecer a função deverá returnar o valor booleano True, caso contrário retorna False.
    '''
    snake = state['snake']
    if snake['body'][0][0] < -290 or snake['body'][0][0] > 290:
        return True
    elif snake['body'][0][1] < -390 or snake['body'][0][1] > 390:
        return True
    else:
        return False

def body_collision(state):
    body = state['snake']['body']
    for w in range(1,len(body)):
        if body[0][0:2] == body[w][0:2]:
            return True
    return False

def check_collisions(state):
    '''
        Função responsável por avaliar se há colisões. Atualmente apenas chama a função que verifica se há colisões com os limites do ambiente. No entanto deverá escrever o código para verificar quando é que a tartaruga choca com uma parede ou com o seu corpo.
    '''
    snake = state['snake']
    bound_col = boundaries_collision(state)
    body_col = body_collision(state)
    if bound_col == True or body_col == True:
        return True
    else:
        return False

def you_lost(state):
    youlost = turtle.Turtle()
    youlost.shape('youlost.gif')
    youlost.ht()
    youlost.pu()
    youlost.goto(0, 400)
    youlost.setheading(270)
    for a in range(4):
        youlost.st()
        youlost.fd(100)
        state['window'].update()
        time.sleep(0.2)
        youlost.ht()
        state['window'].update()
        time.sleep(0.1)
    youlost.st()
    state['window'].update()
    time.sleep(0.2)
    youlost.ht()
    state['window'].update()
    time.sleep(0.1)
    youlost.st()
    state['window'].update()    

def main():
    state = init_state()
    setup(state)
    print("Start! \nComa frutas para ganhar pontos. \nA maçã dourada irá dar mais pontos que a normal. \nO pêssego, para além de pontos extra, reduz o tamanho da cobra. \nO hambúrguer tira pontos e aumenta o tamanho da cobra.")
    while not check_collisions(state):
        state['window'].update()
        check_if_food_to_eat(state)
        move(state)
        speed = SPEED / ( (state['score']/80) + 1) #função para escalar a velocidade (tende para 0)
        if state['score'] < 0:
            time.sleep(SPEED)
        else:
            time.sleep(speed)
    #derrota
    print("YOU LOSE!")
    you_lost(state)
    load_high_score(state)
    if state['score'] > state['high_score']:
        state['new_high_score'] = True 
        print("recorde")
    if state['new_high_score']:
        write_high_score_to_file(state)
    state['window'].exitonclick()

main()