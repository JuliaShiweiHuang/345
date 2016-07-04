
for (int i = 0; i < 30; i++ ) {
    if ( op == 'A' ) {
        read in size;
        totalSize = size + totalSize;

        if ( totalSize < MemorySize ) {
            bool hasWriteInFreeMemory = false;
            //check whether there are any free memory chunk;
            if ( the memory chunk is marked with -1 ) { //if there is any free memory chunk  
                if ( the memory chunk is marked with -1 contigiously ) {
                    combine those memoryChunk space together;
                    for (int i = 0; i < 30; i++ ) {
                        if ( the PIDSize <= memoryChunk ) { //check the size of the memory with this PID;
                            push this PID in front of this memory Chunk;
                            write down this PID number in this memory slot;
                            MemoryChunk = MemoryChunk - thisPIDSize;
                            hasWriteInFreeMemory = true;
                            exit the for loop immediately; //in case the PID is put in the memory mutiple times;
                        }//if
                                      
                    }//for
                }//if
                
            } //if

            else { //no free memory chunk; or memory chunk is less than the PID size;
                if ( hasWriteInFreeMemory == false ) {
                    push the pid at the back of the Queue;
                    write down this PID number;
                }
            }
        } //if  

        else { //memory out of bound;
            skip this PID;
            totalSize = totalSize - thisPIDSize; //decrement size because you increatmented first
            skipCounter ++;

        }
    }//op == A
        
    else { // op == 'D'
        delete the memory with that PID number;
        mark that place with -1;
    }

}


