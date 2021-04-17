# Tema2EGC-Skyroads
[Tema2 - Elemente de Grafica pe Calculator] <br>
Tema presupune implementarea unui Endless Runner, un jucator care parcurge o harta. <br>
> Framework complet: [aici](https://github.com/UPB-Graphics/Framework-EGC) <br>
> Enunt: [aici](https://ocw.cs.pub.ro/courses/egc/teme/2020/02)


#### CONTROLUL JOCULUI
> Jucătorul va fi controlat prin tastele WASD și SPACE. 
>  - ```A / D``` - va schimba coloanele de mers
>  - ```SPACE``` - va fi folosită pentru a sări peste spații
>  - ```W / S``` - pentru a alege viteza de mers
>  - ```C```- se va oscila între modurile de joc first și third person camera


#### IMPLEMENTARE
Harta se genereaza aleator pe minim trei coloane (benzi) de mers astfel încât să nu devină imposibil pentru jucător să treacă peste un anumit spațiu, iar jucătorul se va deplasa doar înainte, având posibilitatea să își schimbe viteza de deplasare și coloana de mers. În timpul jocului, jucătorul va trebui să țină constant cont de cantitatea de combustibil pe care o mai are. Cantitatea de combustibil va scădea treptat odată cu deplasarea. În momentul în care rămâne fără combustibil, jocul se va termina. 

Jocul se poate termina, de asemenea, și dacă jucătorul cade intr-o groapa sau calca pe o platformă rosie (animatie ca jucatorul va cadea din scena). În cadrul jocului vor exista două tipuri de platforme: simple și cu efecte. Platformele simple vor fi de culoare albastră. Platformele care vor acorda jucătorului abilități sau dezavantaje vor fi colorate astfel:

- ```Roșu```: jocul se termină instant
- ```Galben```: jucătorul pierde o parte din combustibil
- ```Portocaliu```: jucătorul este blocat un anumit număr de secunde la o viteză foarte mare (tastele W și S nu au niciun efect în această perioadă)
- ```Verde```: jucătorul recuperează o parte din combustibil

Jucătorul trebuie să țină în permanență cont de cantitatea de combustibil pe care o mai are. Pentru acest lucru se vor folosi două dreptunghiuri suprapuse afișate într-un colț al ecranului (unul alb în spate și unul albastru în față, care se scaleaza pentru a evidenția consumarea combustibilului).
