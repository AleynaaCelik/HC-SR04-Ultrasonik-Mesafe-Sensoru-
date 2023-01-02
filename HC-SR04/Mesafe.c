unsigned int say=0,mesafe=0,sayac=0;


void InitTimer7(){
    RCC_APB1ENR.TIM7EN = 1;
    TIM7_CR1.CEN = 0;
    TIM7_PSC = 0;
    TIM7_CNT=0;
}


void main() {
     InitTimer7();
     GPIO_Digital_Output(&GPIOC_BASE, _GPIO_PINMASK_0);
     GPIO_Digital_Input(&GPIOC_BASE, _GPIO_PINMASK_1);
     GPIO_Digital_Output(&GPIOD_ODR, _GPIO_PINMASK_12|_GPIO_PINMASK_13
                                    |_GPIO_PINMASK_14|_GPIO_PINMASK_15);


while(1)
    {
        GEC :
        TIM7_CR1.CEN=0;                                 // timer durduruluyor.
        TIM7_CNT=0;
        GPIOC_ODR.B0=1;                                 // Trig pinini tetikleme veriliyor.
        delay_us(10);
        GPIOC_ODR.B0=0;                                 // tetikleme kesiliyor.
        sayac=0;

        while(!GPIOC_IDR.B1){                           // Echo pininden 1 gelmesi bekleniyor.
            sayac++;
            delay_us(10);
            if (sayac>10000) goto GEC;
        }

        TIM7_CR1.CEN = 1;
        while(GPIOC_IDR.B1){                            // Timer baslatiliyor.;// Echo pininden 0 gelmesi bekleniyor.
            sayac++;
            delay_us(10);
            if (sayac > 10000) goto GEC;
        }

        TIM7_CR1.CEN=0;// timer durduruluyor.
        say=TIM7_CNT;
        TIM7_CNT=0;
        say=say-200;
        mesafe=(say/834);

        if(mesafe<5 && mesafe>2){
            GPIOD_ODR.B12=1;
            GPIOD_ODR.B13=0;
            GPIOD_ODR.B14=0;
            GPIOD_ODR.B15=0;

        }

        if(mesafe<10 && mesafe>5){
           GPIOD_ODR.B12=0;
            GPIOD_ODR.B13=1;
            GPIOD_ODR.B14=0;
            GPIOD_ODR.B15=0;

        }

        if(mesafe<15 && mesafe>10){
           GPIOD_ODR.B12=0;
            GPIOD_ODR.B13=0;
            GPIOD_ODR.B14=1;
            GPIOD_ODR.B15=0;

        }

        if (mesafe > 15) {
          GPIOD_ODR.B12=0;
          GPIOD_ODR.B13=0;
          GPIOD_ODR.B14=0;
          GPIOD_ODR.B15=1;

        }
    }
}