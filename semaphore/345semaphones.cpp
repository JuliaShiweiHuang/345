  global boolean waiting [n];
        global boolean lock;

        process Pi

        repeat 
           waiting[i] = true;
           key = true;
           while (waiting [i] && key)
              key = testandset (lock);
           waiting [i] = false;

           *critical section* 

           j = (i + 1) % n;                     // give next one a turn
           while ((j != i) && !waiting [j])     // BUT only if next is waiting!
              j = (j + 1) % n;                  // If not waiting, go to next!

           if (j == i)
              lock = false;
           else
              waiting [j] = false;

           *remainder section*

        until done;


        int main () {
           waiting [n] = false;
           lock = false;

           parbegin
              P0;
              P1;
               :
              Pn;
           parend;
        }   






            
        yourtype buffer [N];
        int in = 0;
        int out = 0;



         producer - keeps filling buffer unless full

        yourtype nextp;                 // next item to give to consumer

        repeat
           :
           nextp = blahblah;
           while ((in + 1) % N == out);  // just spin and WAIT!  - full!
           buffer [in] = nextp;
           in = (in + 1) % N;
        until done;                     // i.e., producer is done



        - consumer - keep reading unless empty or done

        yourtype nextc;

        repeat
           while (in == out);           // spin and wait - empty!
           nextc = buffer [out];
           out = (out + 1) % N;
           use (nextc);                 // i.e., "consume"
        until done;
