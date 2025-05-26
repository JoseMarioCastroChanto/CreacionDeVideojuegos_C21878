# Obelisk Defender

Obelisk Defender es un Tower Defense 2.5D para un solo jugador. Hordas de monstruos intentan destruir el obelisco central que da vida al bosque. Pinky, el defensor del obelisco, debe usar su ingenio para crear bombas caminantes y aprovechar su alianza con el antiguo poder del tótem de fuego conocido como Big Bomb.

## 🔧 Compilación y Ejecución

Para compilar Obelisk Defender en Ubuntu:

    make

Para ejecutar el juego:

    make run

Si el ejecutable ya está creado, basta con hacer doble clic sobre él.


## 🎮 Gameplay

Al ejecutar el programa, aparecerá un menú con tres niveles. Usa el mouse (clic izquierdo) para seleccionar el nivel.

Cada nivel dura X segundos (indicados en la esquina superior derecha). Sobrevive durante ese tiempo para ganar.

Al completar un nivel, se mostrará una pantalla de victoria con opciones para avanzar o volver al menú.

En pantalla:

    ⏳ Tiempo restante (esquina superior derecha)

    🔥 Contador de Big Bombs (izquierda del tiempo) — se recarga cada 20 segundos

    ❤️ Vida del jugador = 5 barra verde (esquina superior izquierda)

    🗿 Vida del obelisco = 100 × número de nivel barra azul (esquina superior izquierda)

Si pierdes, aparece la pantalla de derrota con opciones para reintentar o volver al menú.

## ⌨️ Controles

| Tecla   |             Acción                       |
|---------|------------------------------------------|
| W       | Alejarse del usuario (profundidad)       |
| S       | Acercarse al usuario                     |
| A       | Moverse a la izquierda                   |
| D       | Moverse a la derecha                     |
| D + A   | Disparar bomba hacia la izquierda        |
| D + K   | Disparar bomba hacia la derecha          |
| L       | Activar Big Bomb                         |
| P       | Pausar / reanudar                        |


## 🧍‍♂️ Personajes


### 🧨 Bomba

    Proyectil básico.

    Hace 1 de daño.

    Se destruye al colisionar.

### 💥 Big Bomb

    Elimina todos los enemigos no mágicos en pantalla.

### 🟢 Slime

    1 de vida.

    Se mueve horizontalmente y luego rápidamente en vertical.

    Hace 1 de daño continuo al llegar al obelisco.

### 👁️ Eye

    3 de vida.

    Dispara proyectiles en zigzag.

    Daño por colisión: 1 por contacto / proyectil.

### 🍄 Mushroom

    Rápido.

    Se alinea verticalmente con el jugador.

    Hace 1 de daño y se autodestruye al impactar.

### 🦇 Flying Beast

    3 de vida.

    Se lanza velozmente al obelisco.

    Hace 10 de daño por colisión.

### 🪨 Golem

    10 de vida.

    Lento, pero persistente.

    Hace 10 de daño continuo.

### 🧙‍♂️ Mage M

    Invoca Flying Beast, Mushroom o Slime cada 5 segundos.

    8 de vida.

    Hace 1 de daño continuo.

    Inmune a Big Bomb.

### 🧙‍♂️ Mage R

    Invoca Golem cada 8 segundos.

    8 de vida.

    Hace 1 de daño continuo.

    Inmune a Big Bomb.

## 💻 Programación

Juego desarrollado en C++ utilizando:

    SDL2 (image, TTF, mixer)

    Sol

    Lua

    Editor: Visual Studio Code

    Sistema Operativo: Ubuntu

## 👤 Autor

José Mario Castro Chanto