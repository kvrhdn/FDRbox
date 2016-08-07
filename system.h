#ifndef SYSTEM_H
#define SYSTEM_H

/**
 * Initializes the system, should be called before anything else.
 * Blocks if USB hardware is not configured (connected to an USB charger for
 * instance).
 */
void system_initialize( void );

/**
 * Update system tasks.
 */
void system_tasks( void );

#endif // SYSTEM_H
