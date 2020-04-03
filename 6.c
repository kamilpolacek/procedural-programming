#ifndef __PROGTEST__
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */
/*
1. výstupní řetězec je ve formátu ASCIIZ (binární nulou ukončený),
2. zformátovaný text obsahuje slova oddělená vždy pouze jednou mezerou a odstavce oddělené vždy pouze jedním prázdným řádkem (tedy dvojicí znaků odřádkování).
3. Pokud na vstupu není žádné slovo, bude výstupem prázdný řetězec (alokovaná paměť, ale obsahuje pouze ukončující binární nulu).
4. Před prvním slovem na řádku nejsou mezery.
5. Za posledním slovem na řádku nejsou žádné mezery, pouze odřádkování. Odřádkování je i za posledním řádkem textu.
6. Slova jsou zarovnaná vlevo. Pokud se další slovo na danou řádku nevejde, řádka se ukončí a slovo bude umístěno jako první na následující řádce.
7. Funkce vrací návratovou hodnotu NULL, pokud je během formátování nalezeno slovo, které se nevejde na řádku.
*/

char * parseText(const char *src) {
    int spaceN = 0;
    int newLineN = 0;
    int leap = 0;
    int length = strlen(src);
    int noSpacesFlag = 1;
    char *text = (char *) calloc(length + 2, sizeof(char));

    if (length == 0) {
        text[0] = '\0';
        return text;
    }


    for (int i = 0; i < length; i++) {
        if( noSpacesFlag ) {
            if( isspace(src[i]) || iscntrl(src[i]) ){
                leap++;
                continue;
            }
            else
                noSpacesFlag = 0;
        }
        if (src[i] == '\n') {
            if( newLineN == 1 ) {
                text[i - 1 - leap] = '\n';
                spaceN = 0;
                leap++;
                continue;
            }
            if( i == length-1 ) {
                text[i-leap] = src[i];
                break;
            }
            newLineN = 1;
            if( spaceN == 1 ) {
                leap++;
                continue;
            }
            text[i - leap] = ' ';
            spaceN = 1;
            continue;
        } else if (isspace(src[i]) || src[i] == '\t') {
            if (spaceN == 1) {
                leap++;
                continue;
            }
            text[i - leap] = ' ';
            spaceN = 1;
            continue;
        }

        newLineN = 0;
        spaceN = 0;
        text[i - leap] = src[i];
    }

    if ( length > 1 ) {
    if( isspace(text[length-leap-2])  ) {
        text[length-leap-2] = '\n';
        text[length-leap-1] = '\0';
    }
  }
    //printf("%s\n",text );
    return text;
}

char             * wordWrap                                ( int               width,
                                                             const char      * src )
{
    int length=0;
    char *text=NULL;
    char *formatedText=NULL;
    int widthCounter=1;
    int wordLength=0;
    int lastSpace=0;
    int leap=0;




    text = parseText(src);
    length = strlen(text);
    //printf("%s\n",text );
    //printf("%d\n",length );

    //printf(">%c<\n", text[length-1]);
    if( text[0] == '\0' || width >= length ){
      if( text[length-1] == ' ') {
        text[length-1] = '\n';
      }
      if( text[length-1] != '\n') {
        text[length] = '\n';
      }
      return text;

    }

    formatedText = (char*)calloc(length+200,sizeof(char));

    for(int i=0; i<length; i++) {
        /*if( widthCounter == 1 && text[i] == ' ' ) {
            leap++;
            continue;
        }*/

        if( text[i] == '\n' && i != length-1 ) {
            formatedText[i+leap] = text[i];
            formatedText[i+leap+1] = text[i];
            leap++;
            widthCounter=1;
            wordLength=0;
            lastSpace=0;
            continue;
        }
        if( !isspace(text[i]) || ispunct(text[i]) )
            wordLength++;
        else {
            wordLength = 0;
            lastSpace = widthCounter;
        }
        if( wordLength > width ) {
          free(text);
          free(formatedText);
          return NULL;
        }

        if( widthCounter == width+1 && wordLength == 0 ) {
            formatedText[i+leap] = '\n';
            widthCounter=1;
            lastSpace=0;
            wordLength=0;
            continue;
        }
        if( lastSpace+wordLength >= width+1 ) {
            formatedText[i-wordLength+leap] = '\n';
            i = i-wordLength;
            widthCounter=1;
            lastSpace=0;
            wordLength=0;
            continue;
        }

        formatedText[i+leap] = text[i];
        widthCounter++;
    }

    length=strlen(formatedText);

    if( formatedText[length-1] != '\n') {
      formatedText[length] = '\n';
    }

    
    free(text);
    //printf("%s\n",formatedText );
    return formatedText;
}

#ifndef __PROGTEST__
int                main                                     ( void )
{
    char * res=NULL;
    const char * s0 =
            "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus\n"
            "pede, pretium vitae, rhoncus et, auctor sit amet, ligula. Integer volutpat\n"
            "orci et elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus\n"
            "lectus, vitae feugiat purus orci ultricies turpis. Pellentesque habitant\n"
            "morbi tristique senectus et netus et malesuada fames ac turpis egestas. Nam\n"
            "in pede. Etiam eu sem id urna ultricies congue. Vestibulum porttitor\n"
            "ultrices neque. Mauris semper, mauris ut feugiat ultricies, augue purus\n"
            "tincidunt  elit, eu interdum ante nisl ac ante. Pellentesque dui. Vestibulum\n"
            "pretium, augue non cursus pretium, nibh dolor laoreet leo, sed pharetra pede\n"
            "libero non diam.";
    const char * s1 =
            "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus\n"
            "pede, pretium vitae, rhoncus et, auctor sit amet, ligula. Integer volutpat\n"
            "orci et elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus\n"
            "lectus, vitae feugiat purus orci ultricies turpis. Pellentesque habitant\n"
            "morbi tristique senectus et netus et malesuada fames ac turpis egestas. Nam\n"
            "in pede. Etiam eu sem id urna ultricies congue. Vestibulum porttitor\n"
            "ultrices neque. Mauris semper, mauris ut feugiat ultricies, augue purus\n"
            "tincidunt  elit, eu interdum ante nisl ac ante. Pellentesque dui. Vestibulum\n"
            "pretium, augue non cursus pretium, nibh\tdolor laoreet leo, sed pharetra pede\n"
            "libero non diam.\n"
            "\n"
            "Proin est nisi,                     gravida ac, vulputate id, fringilla sit\n"
            "amet, magna. Nam congue cursus magna. In malesuada, velit a gravida sodales,\n"
            "dolor nisl vestibulum orci, sit amet sagittis mauris tellus nec purus. Nulla\n"
            "eget risus. Quisque nec sapien blandit odio convallis ullamcorper. Lorem\n"
            "ipsum dolor sit amet, consectetuer adipiscing elit. Pellentesque cursus.\n"
            "Aliquam tempus neque vitae libero molestie ut auctor.\n"
            "\n"
            "\n"
            "\n"
            "In nec massa eu tortor vulputate suscipit.\tNam tristique magna nec pede. Sed\n"
            "a nisi. Nulla sed augue ut risus placerat porttitor. Ut aliquam. Nulla\n"
            "facilisi. Nulla vehicula nibh ac sapien. Nunc facilisis dapibus ipsum. Donec\n"
            "sed mauris. Nulla quam nisi, laoreet non, dignissim posuere, lacinia nec,\n"
            "turpis. Mauris malesuada nisi sed enim. In hac habitasse platea dictumst.\n"
            "Fusce    faucibus, turpis nec auctor posuere, nulla tellus scelerisque metus,\n"
            "quis molestie mi dui id quam. Mauris vestibulum. Nam ullamcorper.\n"
            "\n";
    res = wordWrap ( 40, s0 );
    assert ( ! strcmp ( res,
                        "Lorem ipsum dolor sit amet, consectetuer\n"
                        "adipiscing elit. Integer metus pede,\n"
                        "pretium vitae, rhoncus et, auctor sit\n"
                        "amet, ligula. Integer volutpat orci et\n"
                        "elit. Nunc tempus, urna at sollicitudin\n"
                        "rutrum, arcu libero rhoncus lectus,\n"
                        "vitae feugiat purus orci ultricies\n"
                        "turpis. Pellentesque habitant morbi\n"
                        "tristique senectus et netus et malesuada\n"
                        "fames ac turpis egestas. Nam in pede.\n"
                        "Etiam eu sem id urna ultricies congue.\n"
                        "Vestibulum porttitor ultrices neque.\n"
                        "Mauris semper, mauris ut feugiat\n"
                        "ultricies, augue purus tincidunt elit,\n"
                        "eu interdum ante nisl ac ante.\n"
                        "Pellentesque dui. Vestibulum pretium,\n"
                        "augue non cursus pretium, nibh dolor\n"
                        "laoreet leo, sed pharetra pede libero\n"
                        "non diam.\n" ) );
    free ( res );

    res = wordWrap ( 120, s0 );
    assert ( ! strcmp ( res,
                        "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus pede, pretium vitae, rhoncus et, auctor sit\n"
                        "amet, ligula. Integer volutpat orci et elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus lectus, vitae\n"
                        "feugiat purus orci ultricies turpis. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac\n"
                        "turpis egestas. Nam in pede. Etiam eu sem id urna ultricies congue. Vestibulum porttitor ultrices neque. Mauris semper,\n"
                        "mauris ut feugiat ultricies, augue purus tincidunt elit, eu interdum ante nisl ac ante. Pellentesque dui. Vestibulum\n"
                        "pretium, augue non cursus pretium, nibh dolor laoreet leo, sed pharetra pede libero non diam.\n" ) );
    free ( res );
    res = wordWrap ( 10, s1 );
    assert ( res == NULL );

    res = wordWrap ( 40, s1 );
    assert ( ! strcmp ( res,
                        "Lorem ipsum dolor sit amet, consectetuer\n"
                        "adipiscing elit. Integer metus pede,\n"
                        "pretium vitae, rhoncus et, auctor sit\n"
                        "amet, ligula. Integer volutpat orci et\n"
                        "elit. Nunc tempus, urna at sollicitudin\n"
                        "rutrum, arcu libero rhoncus lectus,\n"
                        "vitae feugiat purus orci ultricies\n"
                        "turpis. Pellentesque habitant morbi\n"
                        "tristique senectus et netus et malesuada\n"
                        "fames ac turpis egestas. Nam in pede.\n"
                        "Etiam eu sem id urna ultricies congue.\n"
                        "Vestibulum porttitor ultrices neque.\n"
                        "Mauris semper, mauris ut feugiat\n"
                        "ultricies, augue purus tincidunt elit,\n"
                        "eu interdum ante nisl ac ante.\n"
                        "Pellentesque dui. Vestibulum pretium,\n"
                        "augue non cursus pretium, nibh dolor\n"
                        "laoreet leo, sed pharetra pede libero\n"
                        "non diam.\n"
                        "\n"
                        "Proin est nisi, gravida ac, vulputate\n"
                        "id, fringilla sit amet, magna. Nam\n"
                        "congue cursus magna. In malesuada, velit\n"
                        "a gravida sodales, dolor nisl vestibulum\n"
                        "orci, sit amet sagittis mauris tellus\n"
                        "nec purus. Nulla eget risus. Quisque nec\n"
                        "sapien blandit odio convallis\n"
                        "ullamcorper. Lorem ipsum dolor sit amet,\n"
                        "consectetuer adipiscing elit.\n"
                        "Pellentesque cursus. Aliquam tempus\n"
                        "neque vitae libero molestie ut auctor.\n"
                        "\n"
                        "In nec massa eu tortor vulputate\n"
                        "suscipit. Nam tristique magna nec pede.\n"
                        "Sed a nisi. Nulla sed augue ut risus\n"
                        "placerat porttitor. Ut aliquam. Nulla\n"
                        "facilisi. Nulla vehicula nibh ac sapien.\n"
                        "Nunc facilisis dapibus ipsum. Donec sed\n"
                        "mauris. Nulla quam nisi, laoreet non,\n"
                        "dignissim posuere, lacinia nec, turpis.\n"
                        "Mauris malesuada nisi sed enim. In hac\n"
                        "habitasse platea dictumst. Fusce\n"
                        "faucibus, turpis nec auctor posuere,\n"
                        "nulla tellus scelerisque metus, quis\n"
                        "molestie mi dui id quam. Mauris\n"
                        "vestibulum. Nam ullamcorper.\n" ) );
    free ( res );
    res = wordWrap ( 80, s1 );
    assert ( ! strcmp ( res,
                        "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus pede,\n"
                        "pretium vitae, rhoncus et, auctor sit amet, ligula. Integer volutpat orci et\n"
                        "elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus lectus,\n"
                        "vitae feugiat purus orci ultricies turpis. Pellentesque habitant morbi tristique\n"
                        "senectus et netus et malesuada fames ac turpis egestas. Nam in pede. Etiam eu\n"
                        "sem id urna ultricies congue. Vestibulum porttitor ultrices neque. Mauris\n"
                        "semper, mauris ut feugiat ultricies, augue purus tincidunt elit, eu interdum\n"
                        "ante nisl ac ante. Pellentesque dui. Vestibulum pretium, augue non cursus\n"
                        "pretium, nibh dolor laoreet leo, sed pharetra pede libero non diam.\n"
                        "\n"
                        "Proin est nisi, gravida ac, vulputate id, fringilla sit amet, magna. Nam congue\n"
                        "cursus magna. In malesuada, velit a gravida sodales, dolor nisl vestibulum orci,\n"
                        "sit amet sagittis mauris tellus nec purus. Nulla eget risus. Quisque nec sapien\n"
                        "blandit odio convallis ullamcorper. Lorem ipsum dolor sit amet, consectetuer\n"
                        "adipiscing elit. Pellentesque cursus. Aliquam tempus neque vitae libero molestie\n"
                        "ut auctor.\n"
                        "\n"
                        "In nec massa eu tortor vulputate suscipit. Nam tristique magna nec pede. Sed a\n"
                        "nisi. Nulla sed augue ut risus placerat porttitor. Ut aliquam. Nulla facilisi.\n"
                        "Nulla vehicula nibh ac sapien. Nunc facilisis dapibus ipsum. Donec sed mauris.\n"
                        "Nulla quam nisi, laoreet non, dignissim posuere, lacinia nec, turpis. Mauris\n"
                        "malesuada nisi sed enim. In hac habitasse platea dictumst. Fusce faucibus,\n"
                        "turpis nec auctor posuere, nulla tellus scelerisque metus, quis molestie mi dui\n"
                        "id quam. Mauris vestibulum. Nam ullamcorper.\n" ) );
    free ( res );



    return 0;
}
#endif /* __PROGTEST__ */
