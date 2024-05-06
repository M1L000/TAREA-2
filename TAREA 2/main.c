#include "Tdas/extra.h"
#include "Tdas/list.h"
#include "Tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
  char id[100];
  char title[100];
  List *genres;
  List *director;
  float rating;
  int year;
} Film;

void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Base de Datos de Películas");
  puts("========================================");

  puts("1) Cargar Películas");
  puts("2) Buscar por id");
  puts("3) Buscar por director");
  puts("4) Buscar por género");
  puts("5) Buscar por década");
  puts("6) Buscar por rango de calificaciones");
  puts("7) Buscar por década y género");
  puts("8) Salir");
}

int is_equal_str(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2) == 0;
}

int is_equal_int(void *key1, void *key2) {
  return *(int *)key1 == *(int *)key2; 
}

int is_equal_float(void *key1, void *key2) {return *((float *)key1) == *((float *)key2);}

char *espacioInicial(char *str) {
    while (isspace((unsigned char)*str)) str++; 
    return str; 

}

void borrarComillas(char *str) { 

    int len = strlen(str); 
    if (str[0] == '"') { 
        memmove(str, str + 1, len); 
        len--; 
    }
    if (len > 0 && str[len - 1] == '"') { 
        str[len - 1] = '\0'; 
    }

}

List *LISTAGENEROS(Map *pelis_genero, char *genero){
  MapPair *pelis_genero_pair = map_search(pelis_genero, genero);
  List *GENEROS = list_create();
  if (pelis_genero_pair != NULL)
  {
    List *GENEROS = pelis_genero_pair->value;
    return GENEROS;
  }
  return NULL;

}

void imprimirDirector(List *lista){
  int cont = 0;
  char *director = (char*)list_first(lista);

  while(director != NULL){
    if(cont != 0){
      printf(", %s",director);
      }
    else{
      printf("[%s", director);
      cont++;
    }
    director = (char*)list_next(lista);
  }
  printf("]");
}

void ImprimirEnRango(Map* pelis_byid, float min_rating, float max_rating){
  MapPair *pair = map_first(pelis_byid);
  while (pair != NULL)
    {
      Film *peli = pair->value;
      if (peli->rating >= min_rating && peli->rating <= max_rating)
      {
        printf("Título: %s, Director(es): ", peli->title);
        imprimirDirector(peli->director);
        printf(", Año: %d, Rating: %.2f\n",peli->year, peli->rating);
      }
      pair = map_next(pelis_byid);
    }
}

void impresionCargaPeliculas(Map*pelis_byid){

  MapPair *pair = map_first(pelis_byid);
  while (pair != NULL) {
    Film *peli = pair->value;
    printf("ID: %s, Título: %s, Director(es): ", peli->id, peli->title);
    imprimirDirector(peli->director);
    printf(", Año: %d\n", peli->year);
    pair = map_next(pelis_byid); 
  }
}

void insertarDecada(Map* pelis_decada, Film *peli, int arr[], int arr_size) {
    int i;
    int decada = -1;

    for (i = 0; i < arr_size; i++) {
        if (peli->year >= arr[i] && (i == arr_size - 1 || peli->year < arr[i + 1])) {
            decada = arr[i];
            break;
        }
    }

    if (decada != -1) {
        int *decadaKey = malloc(sizeof(int));
        *decadaKey = decada;
        MapPair *pelis_pair = map_search(pelis_decada, decadaKey);

        if (pelis_pair == NULL) {
            List *pelis_list = list_create();
            list_pushBack(pelis_list, peli);
            map_insert(pelis_decada, decadaKey, pelis_list);
        } else {
            free(decadaKey);
            List *pelis_list = pelis_pair->value;
            list_pushBack(pelis_list, peli);
        }
    }
}

void rellenarMapaGeneros(Map *map_bygenre, Map *map_byid) {

  MapPair* iter = map_first(map_byid); 
  while (iter != NULL) { 
      Film *peli = iter->value; 
      char *node = list_first(peli->genres); 
      while (node != NULL) { 
          MapPair *par = map_search(map_bygenre, node);

          if (par == NULL) { 
              List* lista = list_create();
              map_insert(map_bygenre, strdup(node), lista);
              list_pushBack(lista, peli);
          }

          else { 
              List* lista = (List*) par->value; 

              if (lista == NULL) { 
                  lista = list_create(); 
                  par->value = lista; 
              }
              list_pushBack(lista, peli); 
          }
          node = list_next(peli->genres); 
      }
      iter = map_next(map_byid); 
  }
}

void insertarDirector(Map* pelis_director, Map* pelis_byid) {
  MapPair* iter = map_first(pelis_byid); 

  while (iter != NULL) { 

      Film *peli = iter->value; 
      char *node = list_first(peli->director); 

      while (node != NULL) {
          MapPair *par = map_search(pelis_director, node); 

          if (par == NULL) { 
              List* lista = list_create(); 
              map_insert(pelis_director, strdup(node), lista); 

              list_pushBack(lista, peli); 
          }
          else { 
              List* lista = (List*) par->value; 
              if (lista == NULL) { 

                  lista = list_create(); 
                  par->value = lista; 

              }
              list_pushBack(lista, peli); 
          }
          node = list_next(peli->director); 
      }
      iter = map_next(pelis_byid);
  }
}

void cargar_peliculas(Map *pelis_byid, Map *pelis_director, Map *pelis_decada, Map *pelis_genero, Map *pelis_rating) {
  FILE *archivo = fopen("data/Top1500.csv", "r");
  if (archivo == NULL) {
    perror("Error al abrir el archivo"); 
    return;
  }

  char **campos;
  campos = leer_linea_csv(archivo, ','); 

  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    Film *peli = (Film *)malloc(sizeof(Film));
    strcpy(peli->id, campos[1]);        
    strcpy(peli->title, campos[5]);   
    
    peli->director = list_create(); 
    borrarComillas(campos[14]); 
    char *token2 = strtok(campos[14], ","); 
    while (token2 != NULL) { 
        char *clean_token2 = espacioInicial(token2); 
        list_pushBack(peli->director, strdup(clean_token2));
        token2 = strtok(NULL, ",");
    }
    
    peli->genres = list_create(); 
    borrarComillas(campos[11]); 
    char *token = strtok(campos[11], ","); 
    while (token != NULL) { 
        char *clean_token = espacioInicial(token); 
        list_pushBack(peli->genres, strdup(clean_token)); 
        token = strtok(NULL, ","); 
    }

    peli->rating = atof(campos[8]);
    peli->year = atoi(campos[10]); 

    int arr[] = {1950, 1960, 1970, 1980, 1990, 2000, 2010};
    map_insert(pelis_byid, peli->id, peli);
    insertarDecada(pelis_decada, peli, arr, 7);
  }
  fclose(archivo); 

}

void busquedaPorDecadaYGenero(Map* pelis_byid, Map* pelis_genero){
  int year;
  char genero[100];
  printf("Ingrese la decada de la película (ejemplo: 1980): ");
  scanf("%d", &year);
  printf("Ingrese el género de la película: ");
  scanf("%s", genero);
  List *GENEROS = LISTAGENEROS(pelis_genero, genero);
  Film *peli = list_first(GENEROS);
  int cont1 = 0;
  if(GENEROS != NULL){
  while(peli != NULL)
    {
      int cont = 0;
      if(peli->year >= year && peli->year <= year + 9)
      {
        cont1++;
        printf("ID: %s, Título: %s, Director(es): ", peli->id, peli->title);
        imprimirDirector(peli->director);
        printf(", Año: %d", peli->year);
        printf(", Generos: ");
        char *genero = (char *)list_first(peli->genres);
        while (genero != NULL)
          {
            if(cont != 0){
              printf(", %s", genero);
            }else{printf("[%s", genero); cont++;}
            genero = (char *)list_next(peli->genres);
          }
        printf("]\n");
          
      }
      peli = list_next(GENEROS);
    }
  }
  else{
    printf("No hay peliculas de ese genero y decada\n");
  }
  if(cont1 == 0)
  {
    printf("No hay peliculas de ese genero y decada\n");
  }


}

void buscarPorRating(Map *pelis_byid){

  int respuesta = 0;
  printf("Elija el rango de calificaciones a buscar:\n");
  printf("1) 6.0-6.4\n");
  printf("2) 6.5-6.9\n");
  printf("3) 7.0-7.4\n");
  printf("4) 7.5-7.9\n");
  printf("5) 8.0-8.4\n");
  printf("6) 8.5-8.9\n");
  printf("7) 9.0-9.4\n");
  printf("Ingrese su respuesta: ");
  scanf("%d", &respuesta);
  switch(respuesta){
    case 1:
      ImprimirEnRango(pelis_byid, 6.0, 6.4);
      break;
    case 2:
      ImprimirEnRango(pelis_byid, 6.5, 6.9);
    break;
    case 3:
      ImprimirEnRango(pelis_byid, 7.0, 7.4);
    break;
    case 4:
      ImprimirEnRango(pelis_byid, 7.5, 7.9);
    break;
    case 5:
      ImprimirEnRango(pelis_byid, 8, 8.4);
    break;
    case 6:
      ImprimirEnRango(pelis_byid, 8.5, 8.9);
    break;

    case 7:
      ImprimirEnRango(pelis_byid, 9.0, 9.4);
    break;

    default:
      printf("Ingrese una opción válida");
    break;
  }  
}

void buscarPorDecada(Map *pelis_decada){
  int decada = 0;
  printf("Ingrese la década a buscar (ejemplo: 1980): ");
  scanf("%d", &decada);

  MapPair *pair = map_search(pelis_decada, &decada);
  if (pair != NULL) {
    List *pelis = pair->value;
    Film *peli = (Film *)list_first(pelis);
    printf("Películas de la década de %d:\n", decada);
    while (peli != NULL) {
      printf("Título: %s, Director(es): ", peli->title);
      imprimirDirector(peli->director);
      printf(", Año: %d\n", peli->year);
      peli = (Film *)list_next(pelis);
    }

  } else {
    printf("No se encontraron películas de la década de %d.\n", decada);
  }
}

void buscarPorGenero(Map *pelis_genero){
  printf("Ingrese el género que desea buscar: ");
  char genero[100];
  scanf("%s", genero);
  MapPair *pelis_genero_pair = map_search(pelis_genero, genero);
  List *GENEROS = list_create();
  if (pelis_genero_pair != NULL)
  {
    List *pelis_list = pelis_genero_pair->value;
    Film *peli = (Film *)list_first(pelis_list);
    list_pushBack(GENEROS, peli);
    while (peli != NULL)
    {
      printf("Título: %s, Director(es): ", peli->title);
      imprimirDirector(peli->director);
      printf(", Año: %d, Generos: ", peli->year);
      char *genero = (char *)list_first(peli->genres);
      int cont = 0;
      while (genero != NULL)
        {
          if(cont != 0){
            printf(", %s", genero);
          }
          else{printf("[%s", genero); cont++;}
          genero = (char *)list_next(peli->genres);
        }
      printf("]\n");
      peli = (Film *)list_next(pelis_list);
    }

  }
  else
  {
     printf("No hay peliculas de ese genero\n"); 
  }
}

void buscarPorDirector(Map *pelis_director) {

  printf("Ingrese el director que desea buscar: ");
  getchar();
  char director[100];
  scanf("%[^\n]s", director);

  MapPair *pelis_director_pair = map_search(pelis_director, director);
  if (pelis_director_pair != NULL)
  {
    List *pelis_list = pelis_director_pair->value;
    Film *peli = (Film *)list_first(pelis_list);
    while (peli != NULL)
      {
        printf("Título: %s, Director(es): ", peli->title);
        imprimirDirector(peli->director);
        printf(", Año:%d", peli->year);

        peli = (Film *)list_next(pelis_list);
        puts("");
      }

  }
  else
  {
     printf("No hay peliculas de ese director\n"); 
  }
}

void buscar_por_id(Map *pelis_byid) {
  char id[10]; 
  printf("Ingrese el id de la película: ");
  scanf("%s", id); 
  MapPair *pair = map_search(pelis_byid, id);

  if (pair != NULL) {
    Film *peli =
        pair->value; 
    printf("Título: %s, Director(es): ", peli->title);
    imprimirDirector(peli->director);
    printf(", Año: %d\n", peli->year);
  } else {
    printf("La película con id %s no existe\n", id);
  }
}

int main() {
  char opcion; 

  Map *pelis_byid = map_create(is_equal_str);
  Map *pelis_director = map_create(is_equal_str);
  Map *pelis_decada = map_create(is_equal_int);
  Map *pelis_genero = map_create(is_equal_str);
  Map *pelis_rating = map_create(is_equal_float);
  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':
      cargar_peliculas(pelis_byid,pelis_director, pelis_decada,pelis_genero, pelis_rating);
      impresionCargaPeliculas(pelis_byid);
      break;
    case '2':
      buscar_por_id(pelis_byid);
      break;
    case '3':
      insertarDirector(pelis_director, pelis_byid);
      buscarPorDirector(pelis_director);
      break;
    case '4':
      rellenarMapaGeneros(pelis_genero, pelis_byid);
      buscarPorGenero(pelis_genero);
      break;
    case '5':
      buscarPorDecada(pelis_decada);
      break;
    case '6':
      buscarPorRating(pelis_byid);
      break;
    case '7':
      rellenarMapaGeneros(pelis_genero, pelis_byid);
      busquedaPorDecadaYGenero(pelis_byid, pelis_genero);
      break;
    default:
      puts("Ingrese una opción válida");
      break;
    }
    presioneTeclaParaContinuar();

  } while (opcion != '8');

  return 0;
}