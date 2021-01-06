
// unused functions

// from main
//inline int _____m68k_inline_execute(int num_cycles)//inline copy of m68k_execute 
//{
//	/* Make sure we're not stopped */
//	if(!CPU_STOPPED)
//	{
//		/* Set our pool of clock cycles available */
//		SET_CYCLES(num_cycles);
//		m68ki_initial_cycles = num_cycles;
//
//		/* ASG: update cycles */
//		USE_CYCLES(CPU_INT_CYCLES);
//		CPU_INT_CYCLES = 0;
//
//		/* Return point if we had an address error */
//		m68ki_set_address_error_trap(); /* auto-disable (see m68kcpu.h) */
//
//		/* Main loop.  Keep going until we run out of clock cycles */
//		do
//		{
//			/* Set tracing accodring to T1. (T0 is done inside instruction) */
//			m68ki_trace_t1(); /* auto-disable (see m68kcpu.h) */
//
//			/* Set the address space for reads */
//			m68ki_use_data_space(); /* auto-disable (see m68kcpu.h) */
//
//			/* Call external hook to peek at CPU */
//			m68ki_instr_hook(); /* auto-disable (see m68kcpu.h) */
//
//			/* Record previous program counter */
//			REG_PPC = REG_PC;
//
//			/* Read an instruction and call its handler */
//			REG_IR = m68ki_read_imm_16();
//			m68ki_instruction_jump_table[REG_IR]();
//			USE_CYCLES(CYC_INSTRUCTION[REG_IR]);
//
//			/* Trace m68k_exception, if necessary */
//			m68ki_exception_if_trace(); /* auto-disable (see m68kcpu.h) */
//		} while(GET_CYCLES() > 0);
//
//		/* set previous PC to current PC for the next entry into the loop */
//		REG_PPC = REG_PC;
//
//		/* ASG: update cycles */
//		USE_CYCLES(CPU_INT_CYCLES);
//		CPU_INT_CYCLES = 0;
//
//		/* return how many clocks we used */
//		return m68ki_initial_cycles - GET_CYCLES();
//	}
//
//	/* We get here if the CPU is stopped or halted */
//	SET_CYCLES(0);
//	CPU_INT_CYCLES = 0;
//
//	return num_cycles;
//}


//////////from genpp
int gpp_m68k_inline_execute(int num_cycles)
{
	/* Make sure we're not stopped */
	if(!CPU_STOPPED)
	{
		/* Set our pool of clock cycles available */
		SET_CYCLES(num_cycles);
		m68ki_initial_cycles = num_cycles;

		/* ASG: update cycles */
		USE_CYCLES(CPU_INT_CYCLES);
		CPU_INT_CYCLES = 0;

		/* Return point if we had an address error */
		m68ki_set_address_error_trap(); /* auto-disable (see m68kcpu.h) */

		/* Main loop.  Keep going until we run out of clock cycles */
		do
		{
			/* Set tracing accodring to T1. (T0 is done inside instruction) */
			m68ki_trace_t1(); /* auto-disable (see m68kcpu.h) */

			/* Set the address space for reads */
			m68ki_use_data_space(); /* auto-disable (see m68kcpu.h) */

			/* Call external hook to peek at CPU */
			m68ki_instr_hook(); /* auto-disable (see m68kcpu.h) */

			/* Record previous program counter */
			REG_PPC = REG_PC;

			/* Read an instruction and call its handler */
			REG_IR = m68ki_read_imm_16();
			m68ki_instruction_jump_table[REG_IR]();
			USE_CYCLES(CYC_INSTRUCTION[REG_IR]);

			/* Trace m68k_exception, if necessary */
			m68ki_exception_if_trace(); /* auto-disable (see m68kcpu.h) */
		} while(GET_CYCLES() > 0);

		/* set previous PC to current PC for the next entry into the loop */
		REG_PPC = REG_PC;

		/* ASG: update cycles */
		USE_CYCLES(CPU_INT_CYCLES);
		CPU_INT_CYCLES = 0;

		/* return how many clocks we used */
		return m68ki_initial_cycles - GET_CYCLES();
	}

	/* We get here if the CPU is stopped or halted */
	SET_CYCLES(0);
	CPU_INT_CYCLES = 0;

	return num_cycles;
}

void __execute(){ 
    int line;
    system_init();
    system_reset();
    running=1;
    while(running)
    {
        input.pad[0]=inputpad;  
//      dos_update_input();
    //////  system_frame(frame_count);

    status &= ~0x0008;
    if(im2_flag)
        status ^= 0x0010;
    parse_satb(0x80);
//          LockSched();/////
    for(line = 0; line < 262; line ++)
    {
        v_counter = line;
        m68k_inline_execute(487);//487
        if(zirq == 1)  zirq = 0;
        if(!frame_count)
        {
            if(line <  frame_end   ) render_line(line);
            if(line <  frame_end-1 ) parse_satb(0x81 + line);
        }
        if(line <= frame_end)
        {
            counter -= 1;
            if(counter == -1)
            {
                counter = reg[10];
                hint_pending = 1;
                if(reg[0] & 0x10)
                {
                    m68k_set_irq(4);
                }
            }
        }
        else
        {
            counter = reg[10];
        }
        if(line == frame_end)
        {
            status |= 0x0088;
            vint_pending = 1;
            m68k_inline_execute(16);
//            if(!gen_running) break;

            if(reg[1] & 0x20)
            {
                m68k_set_irq(6);
            }

            if(zreset == 1 && zbusreq == 0)  zirq = 1;
        }
 
    }
//              UnlockSched();/////
        /////end function
        if(!frame_count) REDRAW(); //или dos_update_video();
        if(++frame_count>=frame_skip) frame_count=0;

//      		if(++frame_count>=frame_skip){ sys_frame(1); frame_count=0; REDRAW();}
//		else sys_frame(0);

    }
    trash_machine();
    system_shutdown();
    error_shutdown();
}


/*
int onquit(){
  running=0;
  quit=1;
  saveini();////
  return 0;
}

void keypressed(byte keycode){
  switch(keycode){
  case '2': case UP_BUTTON: inputpad |= INPUT_UP; break;
  case '8': case DOWN_BUTTON: inputpad |= INPUT_DOWN; break;
  case '4': case LEFT_BUTTON: inputpad |= INPUT_RIGHT; break;
  case '6': case RIGHT_BUTTON: inputpad |= INPUT_LEFT; break;
  case ENTER_BUTTON:           inputpad |= INPUT_START; break;
  case '5':   inputpad |= INPUT_A; break;
  case '0':   inputpad |= INPUT_B; break;
  case '1':   inputpad |= INPUT_C; break;
  case '3':   inputpad |= INPUT_X; break;
  case '7':   inputpad |= INPUT_Y; break;
  case '9':   inputpad |= INPUT_Z; break;
  case '#':    inputpad |= INPUT_MODE; break;
  }
}

void keyreleased(byte keycode){
  switch(keycode){
  case '2': case UP_BUTTON: inputpad &= ~INPUT_UP; break;
  case '8': case DOWN_BUTTON: inputpad &= ~INPUT_DOWN; break;
  case '4': case LEFT_BUTTON: inputpad &= ~INPUT_RIGHT; break;
  case '6': case RIGHT_BUTTON: inputpad &= ~INPUT_LEFT; break;
  case ENTER_BUTTON:           inputpad &= ~INPUT_START; break;
  case '5':   inputpad &= ~INPUT_A; break;
  case '0':   inputpad &= ~INPUT_B; break;
  case '1':   inputpad &= ~INPUT_C; break;
  case '3':   inputpad &= ~INPUT_X; break;
  case '7':   inputpad &= ~INPUT_Y; break;
  case '9':   inputpad &= ~INPUT_Z; break;
  case '#':    inputpad &= ~INPUT_MODE; break;
  }
}

int onkey(unsigned char keycode, int pressed){ // Нажатии клавиши. Возвращает 0 или 1 для выхода.
  switch(pressed){      
  case KEY_UP: keyreleased(keycode); return 0; // Клавиша отпущена
  case LONG_PRESS: return 0; // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
    if(quit) return 1; //exit
    switch(mode){
    case 3: //frameskip
      if(keycode>='0' && keycode<='9'){ 
        if(!(frame_skip=(keycode-'0')*32)) frame_skip=16;
      }
      mode=0;  break;
    case 0: default: //in game
    switch(keycode){
    case GREEN_BUTTON:
      mode=3; //frameskip
      break;
    case '*': c65=!c65; memset(screen,0,screensize); break;
    case RED_BUTTON:
    case LEFT_SOFT:
      return onquit();
    default: keypressed(keycode);
    }
  }
  }
  return 0;
}
*/ 