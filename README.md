Trabalho Final de CG
====================
uhuhuhuhu

O README principal fica sempre na branch principal então as atualizações sempre serão nele.

Workflow no git
---------------
Nesse projeto o nosso sistema de branchs vai ser parecido com esse [aqui][success] mas com o detalhe que os "feature branches" vão ser baseados nos [Issues e Milestones][issues] do projeto então comentem lá e prestem atenção no que é dito lá.
Eu achei dos tutorials de git, o que vem no [manual][man] e um interativo do [GitHub][try].

Usando git no Windows
--------------------
Eu recomendo usar o [aplicativo do GitHub][githubwin] porque ele é muito fácil e não precisa nem ler o manual ou usar um tutorial, é fácil assim.

Instalando git no LEC
---------------------
Baixe o src do [git][git] e instale com os seguintes comandos
```Shell
make install NO_OPENSSL=1 NO_CURL=1
```
Logue e deslogue do computador e siga esse tutorial [aqui][ssh] :v:  
Agora é só usar os links do SSH que você acha na página do repositório.


[success]: http://nvie.com/posts/a-successful-git-branching-model/ "A successful Git branching model"
[issues]: https://github.com/danisson/final-cg1/issues "Issues"
[man]: http://git-scm.com/docs/gittutorial "gittutorial(7)"
[try]: https://try.github.io/ "Try Git"
[githubwin]: https://windows.github.com/ "Github para Windows"
[git]: https://github.com/git/git/archive/master.zip
[ssh]: https://help.github.com/articles/generating-ssh-keys "Generating SSH keys"