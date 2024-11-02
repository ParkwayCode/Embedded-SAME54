#include <atmel_start.h>

#define TIMER_INTERVAL_SLOW 500
#define TIMER_INTERVAL_FAST 100

static struct timer_task TIMER_0_task1;

static void TIMER_0_task1_cb(const struct timer_task *const timer_task)
{
	gpio_toggle_pin_level(LED_0);
}

void configure_timer(uint16_t interval);
volatile bool button_pressed = false;

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	// Hier ist ein Kommentar
	configure_timer(TIMER_INTERVAL_SLOW);
	
	/* Replace with your application code */
	while (1) {
		
		if(gpio_get_pin_level(SW0) == false){
			if(!button_pressed){
				button_pressed = true;
				timer_stop(&TIMER_0);
				timer_remove_task(&TIMER_0, &TIMER_0_task1);
				configure_timer(TIMER_INTERVAL_FAST);
			}
		}else{
			if(button_pressed){
				button_pressed = false;
				timer_stop(&TIMER_0);
				timer_remove_task(&TIMER_0, &TIMER_0_task1);
				configure_timer(TIMER_INTERVAL_SLOW);
			}
		}
		
	}
}


// Initialisierung und Konfiguration des Timers
void configure_timer( uint16_t interval ) {

	TIMER_0_task1.interval = interval;
	TIMER_0_task1.cb = TIMER_0_task1_cb;
	TIMER_0_task1.mode = TIMER_TASK_REPEAT;

	// Timer starten
	timer_add_task(&TIMER_0, &TIMER_0_task1);  // Nutze TIMER_0
	//timer_stop(&TIMER_0);  // Standardm��ig Timer stoppen
	timer_start(&TIMER_0);
}
