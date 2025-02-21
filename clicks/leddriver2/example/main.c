/*!
 * \file 
 * \brief LedDriver2 Click example
 * 
 * # Description
 * This app enables usage of compact, high-efficiency, fixed frequency,
 * synchronous step-up converter, optimized to drive one LED with the constant current.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - GPIO,
 * PWM initialization set PWM duty cycle and start PWM.
 * 
 * ## Application Task  
 * This is an example that demonstrates the use of the LED Driver 2 Click board.
 * This example shows the automatic control halogen bulb light intensity,
 * the first intensity of light is rising and then the intensity of light is falling.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * \author Nikola Peric
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "leddriver2.h"

// ------------------------------------------------------------------ VARIABLES

static leddriver2_t leddriver2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver2_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    leddriver2_cfg_setup( &cfg );
    LEDDRIVER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver2_init( &leddriver2, &cfg );

    leddriver2_pwm_start( &leddriver2 );
}

void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    leddriver2_set_duty_cycle ( &leddriver2, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms( 500 );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
