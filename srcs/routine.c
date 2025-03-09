#include "../include/philo.h"

/**
 * Routine function for philosopher threads.
 *
 * This function represents the routine of a philosopher in the dining philosophers problem.
 * Each philosopher will repeatedly perform the following actions in a loop until they are dead:
 * - Take a fork
 * - Sleep
 * - Think
 *
 * The function checks if the philosopher is dead before and after each action to ensure
 * that the philosopher stops performing actions if they are dead.
 *
 * @param philo Pointer to the philosopher structure.
 * @return NULL when the philosopher is dead.
 */


 /**
  * Fonctions manquantes pour le projet :
  * - checker le nb de philo et si s'est gigit
  * - realiser la partie du monitoring :
  * 	-> compteur pour le nombre de fois ou il a mangé (philo[i]) grace a data->has_eaten/ing/ate entre les deux boucle
  *		-> check_meals/kill_philo/usleep (2 if) et usleep(400) comprendre pourquoi
  */