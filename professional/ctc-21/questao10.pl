genero(amnesia, suspense).
genero(babel, drama).
genero(capote, drama).
genero(casablanca, romance).
genero(matrix, ficcao).
genero(rebecca, suspense).
genero(shrek, aventura).
genero(sinais, ficcao).
genero(spartacus, acao).
genero(superman, aventura).
genero(titanic, romance).
genero(tubarao, suspense).
genero(volver, drama).

diretor(amnesia, nolan).
diretor(babel, inarritu).
diretor(capote, miller).
diretor(casablanca, curtiz).
diretor(matrix, wachowsk).
diretor(rebecca, hitchcock).
diretor(shrek, adamson).
diretor(sinais, shymalan).
diretor(spartacus, kubnik).
diretor(superman, donner).
diretor(titanic, cameron).
diretor(tubarao, spielberg).
diretor(volver, almodovar).

ano(amnesia, 2000).
ano(babel, 2006).
ano(capote, 2005).
ano(casablanca, 1942).
ano(matrix, 1999).
ano(rebecca, 1940).
ano(shrek, 2001).
ano(sinais, 2002).
ano(spartacus, 1980).
ano(superman, 1978).
ano(titanic, 1997).
ano(tubarao, 1975).
ano(volver, 2008).

minutos(amnesia, 113).
minutos(babel, 142).
minutos(capote, 98).
minutos(casablanca, 102).
minutos(matrix, 136).
minutos(rebecca, 130).
minutos(shrek, 90).
minutos(sinais, 106).
minutos(spartacus, 184).
minutos(superman, 143).
minutos(titanic, 194).
minutos(tubarao, 124).
minutos(volver, 121).

classico(Filme) :- ano(Filme, Lancamento), Lancamento < 1980.

