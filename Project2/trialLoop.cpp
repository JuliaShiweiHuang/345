


for ( int i = 0; i < 200; i++ ) {
	for ( int j = 0; j < 60; j++ ) {
			if ( parallelArray[i][j] == 1 ) {
					if ( array[i][j+1] == 'c' ) {
						//function;
						array[i][j+2] = toupper( array[i][j+2] );
					}
					if ( array[i][j+1] == 'C' ) {
						//function;
						
						bool noSpace = true;
						while ( noSpace ) {
							
							for ( int insideOneRow = j+2; insideOneRow < 60 - j; insideOneRow++ ) {
								if ( array[i][insideOneRow] == ' ' ) {
									noSpace = false;
								}
								else {
									array[i][insideOneRow] = toupper ( array[i][insideOneRow] );
									noSpace = true;
								}
							}
						}

					}

					else { // array[i][j+1] == 'u'
						//function;
					}
			}
	}//for
}//for
