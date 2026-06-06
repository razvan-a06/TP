‼️ IMPORTANT ‼️
Pentru ca programul să funcționeze corect, trebuie să creați un nou folder în interiorul directorului clonat și să mutați acolo fișierul executabil. Fișierele .json cu cuvinte trebuie să rămână în folderul principal!

Pentru Linux    
Deschide terminalul în folderul proiectului și folosește make:

1. Compilează jocul:  
   make  
2. Creează folderul nou și mută executabilul în el:  
   mkdir build  
   mv hangman build/  
3. Intră în noul folder și rulează jocul:  
   cd build  
   ./hangman  
  
(Pentru a curăța fișierele .o generate în folderul principal, folosește make clean).  
  
Pentru Windows  
Puteți utiliza direct fișierul executabil .exe din repo, cu mențiunea să fie așezat într-un sub-folder creat de dumneavoastră, exact conform instrucțiunilor de mai sus.
