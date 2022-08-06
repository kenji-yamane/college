# Projeto de controle de um multicóptero 6DOF

## Simular respostas ao degrau e rampa

Rode o arquivo `respostas.m`, passando como parâmetro uma `string`
que pode ser uma das seguintes:

| Nome      | Descrição |
| ----------- | ----------- |
| `xstep`      | Resposta em degrau para o controle do eixo x       |
| `ystep`      | Resposta em degrau para o controle do eixo y       |
| `zstep`      | Resposta em degrau para o controle do eixo z       |
| `psistep`      | Resposta em degrau para o controle do ângulo de rolamento      |
| `xramp`      | Resposta à rampa para o controle do eixo x       |
| `yramp`      | Resposta à rampa para o controle do eixo y       |
| `zramp`      | Resposta à rampa para o controle do eixo z       |
| `xhighstep`      | Resposta em degrau elevado para o controle do eixo x       |
| `yhighstep`      | Resposta em degrau elevado para o controle do eixo y       |

## Simular situações complexas para o drone seguir

Rode o arquivo `simularDrone.m`, passando como parâmetro uma `string`
que pode ser uma das seguintes:

| Nome      | Descrição |
| ----------- | ----------- |
| `sela`      | Simula o drone seguindo um caminho por um cubo que se assemelha a uma sela  |
| `quadrado`      | Simula o drone seguindo um quadrado, variando o z  |
| `espiral`      | Simula o drone seguindo uma espiral, cujo eixo é o z  |
| `bicone`      | Simula o drone seguindo a superfície de um bicone  |
| `lissajous`      | Segue uma curva de Lissajous  |

## Cálculos para se linearizar o sistema e deduzir as funções de transferência

Os arquivos dentro de `contas/` consistem nos cálculos simbólicos para se obter as equações
necessárias.

