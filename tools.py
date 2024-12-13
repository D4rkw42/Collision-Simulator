# tool kit para desenvolvimento de projetos cmake - by D4rkw42

import sys, os
import subprocess

application = "geometric-collisions-simulator.exe"

# flushing
os.system("cls")

# comandos listados
command_list = ("run", "cmake", "build")
commands = []

# comandos

def run_command(*args): # executa o aplicativo
    target = sys.path[0] + "\\build\\" + application

    print(f"[Tools.py] Executando {application}...")
    subprocess.call([target])

def cmake_command(*args): # gera o makefile (para arquivos novos)
    print("[Tools.py] Gerando Makefile com CMake...")
    os.system("cmake . -G \"MinGW Makefiles\" -B build -DCMAKE_BUILD_TYPE=Debug")

def build_command(*args): # faz a build do aplicativo
    print(f"[Tools.py] Gerando {application}...")
    os.system("cmake --build build")

# adicionando comandos
commands.append(("run", run_command))
commands.append(("cmake", cmake_command))
commands.append(("build", build_command))

#

if __name__ == "__main__":
    args = sys.argv

    if len(args) < 2:
        print("[Tools.py] Indefinição de comando!")
        exit()

    # executando os comandos corretos
    for cmd in commands:
        name = args[1]

        if cmd[0] == name:
            cmd[1](args)
            exit()

    print("[Tools.py] Comando inválido!")
