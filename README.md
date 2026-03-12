*Este proyecto ha sido creado como parte del currículo de 42 por andtruji.*

Philosophers es una implementación de es una simulación del clásico "Problema de los filósofos comensales" de Edsger Dijkstra. El objetivo principal es resolver un problema de concurrencia y sincronización de hilos en C.
El proyecto explora cómo evitar el deadlock (bloqueo mutuo) y las condiciones de carrera (race conditions) mientras varios filósofos sentados a una mesa circular intentan comer, pensar y dormir sin morir de hambre, compartiendo un número limitado de cubiertos (mutex).

Compilación
Para compilar el proyecto, clona el repositorio y ejecuta:

make

Ejecución
Una vez compilado, puedes lanzar el programa de la siguiente manera:

./philo [num_filosofos] [tiempo_morir] [tiempo_comer] [tiempo_dormir] [comidas_opcionales]

e.g.
./philo 4 410 200 200
 Nadie deberia morir.

Recursos
  Referencias

Pthreads manual (POSIX threads)
Mutexes en C - Tutorial de geeksforgeeks

Uso de IA
Se ha utilizado IA para:
Lógica de sincronización: Análisis de algoritmos para prevenir el deadlock (numeración de cubiertos).
Herramientas de diagnóstico: Ayuda para interpretar errores de Valgrind --tool=helgrind y ThreadSanitizer.
Refactorización: Mejora de la estructura de la estructura t_data para evitar variables globales.
