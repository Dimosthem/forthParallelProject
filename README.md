# forthParallelProject  
Εργασία του Δημοσθένη Μπουναρέλη , ΑΕΜ = 9431.  
Λεπτομέρειες περί του κώδικα.  
Τα αποτελέσματα αποθηκεύονται στο resultFile.txt
Ο χρόνος μετριέται σε ms και δεν μετρά την μετατροπή πινάκων σε blocked μορφή (ούτως ή άλλως είναι μηδαμινός).   
Μετράει όμως όλα τα υπόλοιπα.
Αυτό το i που εκτυπώνεται είναι για να δείχνει ότι ο κώδικας προχωρά. Έχει maximum τιμή την n+1 (έτσι όπως όρισα το n).  
Όπως θα δείτε και από την ώρα ανεβάσματος του κώδικα, δεν είχα χρόνο να προσθέσω σχόλια σε αυτόν, επομένως είναι δυσανάγνωστος και χωρίς σχόλια.  
Στην αναφορά, εξηγώ τι σημαίνει το k και το n, είναι αριθμός διαμερίσεων (κοψιμάτων) του πίνακα.  
Για να τρέξετε έναν απλό πολλαπλασιασμό.  
Θα κάνετε πρώτα ./buildNotPar και ύστερα ./serialProgram πρώτος_πίνακας δεύτερος_πίνακας k n. Για απλό πολλαπλασιασμό , βάλτε k = n = 0.  
Για να τρέξετε με MPI.  
./buildMPI.sh και μετά mpirun -np αριθμος_processes ./mpiProgram πρώτος_πίνακας δεύτερος_πίνακας k n  
Για openMP  
./buildParallel και ./openMPProgram πρώτος_πίνακας δεύτερος_πίνακας k n    
Για MPI με openMP  
./buildMPIpar.sh και mpirun -np number_of_processes ./mpiProgramPar πρώτος_πίνακας δεύτερος_πίνακας k n  

Για να τρέξετε filtered πολλαπλασιασμό    
./buildNotParFiltered.sh και έπειτα ./serialProgramFiltered πρώτος_πίνακας δεύτερος_πίνακας πίνακας_φίλτρο   

Ελπίζω ότι δεν έκανα κάποιο μοιραίο τυπογραφικό γράφοντας λάθος οδηγίες και ελπίζω να μην ανέβασα λάθος αρχεία.  
Καλή σας ημέρα.

