#include "usmart.h"
#include "usart.h"
#include "sys.h"
 
char *sys_cmd_tab[]=
{
	"?",
	"help",
	"list",
	"id",
	"hex",
	"dec",
	"runtime",	   
};	    


uint8_t usmart_sys_cmd_exe(uint8_t *str)
{
	uint8_t i;
	uint8_t sfname[MAX_FNAME_LEN];//զ؅Ѿ֘گ˽Ļ
	uint8_t pnum;
	uint8_t rval;
	uint32_t res;  
	res=usmart_get_cmdname(str,sfname,&i,MAX_FNAME_LEN);//փսָ®ָܰ®Ӥ׈
	if(res)return USMART_FUNCERR;//խϳքָ® 
	str+=i;	 	 			    
	for(i=0;i<sizeof(sys_cmd_tab)/4;i++)//֧Ԗքϵͳָ®
	{
		if(usmart_strcmp(sfname,sys_cmd_tab[i])==0)break;
	}
	switch(i)
	{					   
		case 0:
		case 1://ѯ׺ָ®
			//printf("\r\n");
/*#if USMART_USE_HELP
			printf("------------------------USMART V3.1------------------------ \r\n");
			printf("    USMARTˇԉALIENTEKߪעքһٶ©ȉքԮࠚַ˔ۥݻةݾ,ͨڽ \r\n");
			printf("̼,ţࠉӔͨڽԮࠚ׺˖ַԃԌѲoĦքɎێگ˽,Ңִѐ.ӲՋ,ţࠉ\r\n");
			printf("Ӕ̦Ӣټلگ˽քˤɫӎ˽(֧Ԗ˽ؖ(10/16޸׆)bؖػԮbگ˽ɫ\r\n");	  
			printf("ࠚַ֘ֈطΪӎ˽),եٶگ˽خנ֧Ԗ10ٶˤɫӎ˽,Ң֧Ԗگ˽׵ \r\n");
			printf("ܘֵДʾ.тնӎ˽Дʾ޸׆ʨ׃٦Ŝ,тն޸׆תۻ٦Ŝ.\r\n");
			printf("ܼ˵֧Ԗ:www.openedv.com\r\n");
			printf("USMARTԐ7ٶϵͳļ®:\r\n");
			printf("?:      ܱȡѯ׺хϢ\r\n");
			printf("help:   ܱȡѯ׺хϢ\r\n");
			printf("list:   ࠉԃքگ˽ҭ\r\n\n");
			printf("id:     ࠉԃگ˽քIDҭ\r\n\n");
			printf("hex:    ӎ˽16޸׆Дʾ,۳ٺࠕٱ+˽ִܴؖѐ޸׆תۻ\r\n\n");
			printf("dec:    ӎ˽10޸׆Дʾ,۳ٺࠕٱ+˽ִܴؖѐ޸׆תۻ\r\n\n");
			printf("runtime:1,ߪǴگ˽Ջѐ݆ʱ;0,ژҕگ˽Ջѐ݆ʱ;\r\n\n");
			printf("ȫд֕ԌѲҠдٱʽˤɫگ˽Ļܰӎ˽ҢӔܘӵݼޡ˸.\r\n");    
			printf("--------------------------ALIENTEK------------------------- \r\n");
#else
			printf("ָ®ʧЧ\r\n");
#endif*/
			break;
		case 2://өѯָ®
			//printf("\r\n");
			//printf("-------------------------گ˽ȥե--------------------------- \r\n");
			for(i=0;i<usmart_dev.fnum;i++)//printf("%s\r\n",usmart_dev.funs[i].name);
			//printf("\r\n");
			break;	 
		case 3://өѯID
			//printf("\r\n");
			//printf("-------------------------گ˽ ID --------------------------- \r\n");
			for(i=0;i<usmart_dev.fnum;i++)
			{
				usmart_get_fname((uint8_t*)usmart_dev.funs[i].name,sfname,&pnum,&rval);//փսѾ֘گ˽Ļ 
				//printf("%s id is:\r\n0X%08X\r\n",sfname,usmart_dev.funs[i].func); //ДʾID
			}
			//printf("\r\n");
			break;
		case 4://hexָ®
			//printf("\r\n");
			usmart_get_aparm(str,sfname,&i);
			if(i==0)//ӎ˽ֽӣ
			{
				i=usmart_str2num(sfname,&res);	   	//݇¼كӎ˽	
				if(i==0)						  	//޸׆תۻ٦Ŝ
				{
					//printf("HEX:0X%X\r\n",res);	   	//תΪ16޸׆
				}else if(i!=4)return USMART_PARMERR;//ӎ˽խϳ.
				else 				   				//ӎ˽Дʾʨ֨٦Ŝ
				{
					//printf("16޸׆ӎ˽Дʾ!\r\n");
					usmart_dev.sptype=SP_TYPE_HEX;  
				}

			}else return USMART_PARMERR;			//ӎ˽խϳ.
			//printf("\r\n"); 
			break;
		case 5://decָ®
			//printf("\r\n");
			usmart_get_aparm(str,sfname,&i);
			if(i==0)//ӎ˽ֽӣ
			{
				i=usmart_str2num(sfname,&res);	   	//݇¼كӎ˽	
				if(i==0)						   	//޸׆תۻ٦Ŝ
				{
					//printf("DEC:%lu\r\n",res);	   	//תΪ10޸׆
				}else if(i!=4)return USMART_PARMERR;//ӎ˽խϳ.
				else 				   				//ӎ˽Дʾʨ֨٦Ŝ
				{
					//printf("10޸׆ӎ˽Дʾ!\r\n");
					usmart_dev.sptype=SP_TYPE_DEC;  
				}

			}else return USMART_PARMERR;			//ӎ˽խϳ. 
			//printf("\r\n"); 
			break;	 
		case 6://runtimeָ®,ʨ׃ˇرДʾگ˽ִѐʱݤ
			//printf("\r\n");
			usmart_get_aparm(str,sfname,&i);
			if(i==0)//ӎ˽ֽӣ
			{
				i=usmart_str2num(sfname,&res);	   		//݇¼كӎ˽	
				if(i==0)						   		//ׁȡַָ֨֘˽ߝ٦Ŝ
				{
					if(USMART_ENTIMX_SCAN!=0)//printf("\r\nError! \r\nTo EN RunTime function,Please set USMART_ENTIMX_SCAN = 1 first!\r\n");//Ѩխ
					{
						usmart_dev.runtimeflag=res;
//						if(usmart_dev.runtimeflag==0)//printf("Run Time Calculation ON\r\n");
//						else //printf("Run Time Calculation OFF\r\n"); 
					}
				}else return USMART_PARMERR;   			//δոӎ˽,ܲ֟ӎ˽խϳ	 
 			}else return USMART_PARMERR;				//ӎ˽խϳ. 
			//printf("\r\n"); 
			break;	    
		default://؇רָ®
			return USMART_FUNCERR;
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
//ӆֲעӢ:Ѿ}ˇӔstm32Ϊ},ɧڻҪӆֲսǤ̻mcu,ȫضРӦўل.
//usmart_reset_runtime,ȥԽگ˽Ջѐʱݤ,lͬ֨ʱǷք݆˽݄զǷӔܰҪ־λһǰȥ£.Ңʨ׃טװ՘ֵΪخճ,ӔخճО׈քғӤ݆ʱʱݤ.
//usmart_get_runtime,ܱȡگ˽Ջѐʱݤ,ͨڽׁȡCNTֵܱȡ,ԉԚusmartˇͨڽא׏ַԃքگ˽,̹Ӕ֨ʱǷא׏һՙԐЧ,ՋʱخճО׈
//ֻŜͳ݆2ՎCNTքֵ,Ҳߍˇȥ£۳+ӧԶһՎ,ձӧԶӬڽ2Վ,ûרԦm,̹Ӕخճғʱ,࠘׆՚:2*݆˽ǷCNT*0.1ms.הSTM324˵,ˇ:13.1sسԒ
//Ǥ̻ք:TIM4_IRQHandlerۍTimer2_Init,ѨҪٹߝMCU֣ؔ͘ѐўل.ȷѣ݆˽Ƿ݆˽ƵÊΪ:10Khzܴࠉ.­΢,֨ʱǷһҪߪǴؔ֯טװ՘٦Ŝ!!

#if USMART_ENTIMX_SCAN==1
//شλruntime
//ѨҪٹߝ̹ӆֲսքMCUք֨ʱǷӎ˽޸ѐўل
void usmart_reset_runtime(void)
{
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);//ȥԽא׏Ҫ־λ 
	TIM_SetAutoreload(TIM4,0XFFFF);//ݫטװ՘ֵʨ׃սخճ
	TIM_SetCounter(TIM4,0);		//ȥࠕ֨ʱǷքCNT
	usmart_dev.runtime=0;	
}
//ܱփruntimeʱݤ
//׵ܘֵ:ִѐʱݤ,եλ:0.1ms,خճғʱʱݤΪ֨ʱǷCNTֵք2Ѷ*0.1ms
//ѨҪٹߝ̹ӆֲսքMCUք֨ʱǷӎ˽޸ѐўل
uint32_t usmart_get_runtime(void)
{
	if(TIM_GetFlagStatus(TIM4,TIM_FLAG_Update)==SET)//՚Ջѐǚݤ,Ӻʺ֨ʱǷӧԶ
	{
		usmart_dev.runtime+=0XFFFF;
	}
	usmart_dev.runtime+=TIM_GetCounter(TIM4);
	return usmart_dev.runtime;		//׵ܘ݆˽ֵ
}
//ЂĦ֢}ٶگ˽,؇USMARTگ˽,؅ս֢o,޶޶׽ңӆֲ. 
//֨ʱǷ4א׏ؾϱԌѲ	 
void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET)//ӧԶא׏
	{
		usmart_dev.scan();	//ִѐusmartɨĨ	
		TIM_SetCounter(TIM4,0);		//ȥࠕ֨ʱǷքCNT
		TIM_SetAutoreload(TIM4,100);//ܖشԭ4քʨ׃		    				   				     	    	
	}				   
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //ȥԽא׏Ҫ־λ    
}
//ʹŜ֨ʱǷ4,ʹŜא׏.
void Timer4_Init(uint16_t arr,uint16_t psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //TIM4ʱדʹŜ 
 
	//TIM4Եʼۯʨ׃
 	TIM_TimeBaseStructure.TIM_Period = arr; //ʨ׃՚Ђһٶټт˂ݾװɫܮ֯քؔ֯טװ՘݄զǷלǚքֵ	 ݆˽ս5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ʨ׃ԃ4طΪTIMxʱדƵÊԽ˽քԤؖƵֵ  10Khzք݆˽ƵÊ  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //ʨ׃ʱדؖٮ:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMвʏ݆˽ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //ٹߝTIM_TimeBaseInitStructאָ֨քӎ˽ԵʼۯTIMxքʱݤܹ˽եλ
 
	TIM_ITConfig( TIM4, TIM_IT_Update|TIM_IT_Trigger, ENABLE );//TIM4 Պѭټтìԥעא׏

	//TIM4א׏ؖةƤ׃
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3א׏
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //ЈռԅЈܶ03ܶ
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //ՓԅЈܶ3ܶ
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨրѻʹŜ
	NVIC_Init(&NVIC_InitStructure);  //ٹߝNVIC_InitStructאָ֨քӎ˽Եʼۯ΢ʨNVIC݄զǷ

	TIM_Cmd(TIM4, ENABLE);  //ʹŜTIM4							 
}
#endif
////////////////////////////////////////////////////////////////////////////////////////
//ԵʼۯԮࠚ࠘׆Ƿ
//sysclk:ϵͳʱדèMhzé
void usmart_init(uint8_t sysclk)
{
#if USMART_ENTIMX_SCAN==1
	Timer4_Init(1000,(uint32_t)sysclk*100-1);//ؖƵ,ʱדΪ10K ,100msא׏һՎ,עӢ,݆˽ƵÊҘѫΪ10Khz,Ӕۍruntimeեλ(0.1ms)ͬҽ.
#endif
	usmart_dev.sptype=1;	//ʮ¹޸׆Дʾӎ˽
}		
//Փstrאܱȡگ˽Ļ,id,ܰӎ˽хϢ
//*str:ؖػԮָ֫.
//׵ܘֵ:0,ʶҰԉ٦;Ǥ̻,խϳպë.
uint8_t usmart_cmd_rec(uint8_t*str) 
{
	uint8_t sta,i,rval;//״̬	 
	uint8_t rpnum,spnum;
	uint8_t rfname[MAX_FNAME_LEN];//՝զࠕݤ,ԃԚզ؅ޓ˕սքگ˽Ļ  
	uint8_t sfname[MAX_FNAME_LEN];//զ؅Ѿ֘گ˽Ļ
	sta=usmart_get_fname(str,rfname,&rpnum,&rval);//փսޓ˕սք˽ߝքگ˽Ļܰӎ˽ٶ˽	  
	if(sta)return sta;//խϳ
	for(i=0;i<usmart_dev.fnum;i++)
	{
		sta=usmart_get_fname((uint8_t*)usmart_dev.funs[i].name,sfname,&spnum,&rval);//փսѾ֘گ˽Ļܰӎ˽ٶ˽
		if(sta)return sta;//Ѿ֘ޢ϶Ԑϳ	  
		if(usmart_strcmp(sfname,rfname)==0)//Рֈ
		{
			if(spnum>rpnum)return USMART_PARMERR;//ӎ˽խϳ(ˤɫӎ˽҈Դگ˽ӎ˽ʙ)
			usmart_dev.id=i;//݇¼گ˽ID.
			break;//͸Զ.
		}	
	}
	if(i==usmart_dev.fnum)return USMART_NOFUNCFIND;	//δ֒սƥƤքگ˽
 	sta=usmart_get_fparam(str,&i);					//փսگ˽ӎ˽ٶ˽	
	if(sta)return sta;								//׵ܘխϳ
	usmart_dev.pnum=i;								//ӎ˽ٶ˽݇¼
    return USMART_OK;
}
//usamrtִѐگ˽
//كگ˽ԃԚخוִѐՓԮࠚ˕սքԐЧگ˽.
//خנ֧Ԗ10ٶӎ˽քگ˽,ټנքӎ˽֧ԖҲۜɝӗʵЖ.һڽԃքۜʙ.һѣ5ٶسԒքӎ˽քگ˽ӑޭۜʙݻ.
//كگ˽ܡ՚Ԯࠚղӡִѐȩ࠶.Ӕ:"گ˽Ļ(ӎ˽1ìӎ˽2...ӎ˽N)=׵ܘֵ".քюʽղӡ.
//ձִ̹ѐքگ˽ûԐ׵ܘֵքʱ۲,̹ղӡք׵ܘֵˇһٶϞӢӥք˽ߝ.
void usmart_exe(void)
{
	uint8_t id,i;
	uint32_t res;		   
	uint32_t temp[MAX_PARM];//ӎ˽תۻ,ʹ֧֮ԖؖػԮ 
	uint8_t sfname[MAX_FNAME_LEN];//զ؅Ѿ֘گ˽Ļ
	uint8_t pnum,rval;
	id=usmart_dev.id;
	if(id>=usmart_dev.fnum)return;//һִѐ.
	usmart_get_fname((uint8_t*)usmart_dev.funs[id].name,sfname,&pnum,&rval);//փսѾ֘گ˽Ļ,ܰӎ˽ٶ˽ 
	//printf("\r\n%s(",sfname);//ˤԶֽҪִѐքگ˽Ļ
	for(i=0;i<pnum;i++)//ˤԶӎ˽
	{
		if(usmart_dev.parmtype&(1<<i))//ӎ˽ˇؖػԮ
		{
			//printf("%c",'"');			 
			//printf("%s",usmart_dev.parm+usmart_get_parmpos(i));
			//printf("%c",'"');
			temp[i]=(uint32_t)&(usmart_dev.parm[usmart_get_parmpos(i)]);
		}
		else						  //ӎ˽ˇ˽ؖ
		{
			temp[i]=*(uint32_t*)(usmart_dev.parm+usmart_get_parmpos(i));
//			if(usmart_dev.sptype==SP_TYPE_DEC)//printf("%lu",temp[i]);//10޸׆ӎ˽Дʾ
//			else //printf("0X%X",temp[i]);//16޸׆ӎ˽Дʾ 	   
		}
//		if(i!=pnum-1)//printf(",");
	}
	//printf(")");
	usmart_reset_runtime();	//݆ʱǷȥ£,ߪʼ݆ʱ
	switch(usmart_dev.pnum)
	{
		case 0://Ϟӎ˽(void`э)											  
			res=(*(uint32_t(*)())usmart_dev.funs[id].func)();
			break;
	    case 1://Ԑ1ٶӎ˽
			res=(*(uint32_t(*)())usmart_dev.funs[id].func)(temp[0]);
			break;
	    case 2://Ԑ2ٶӎ˽
			res=(*(uint32_t(*)())usmart_dev.funs[id].func)(temp[0],temp[1]);
			break;
	    case 3://Ԑ3ٶӎ˽
			res=(*(uint32_t(*)())usmart_dev.funs[id].func)(temp[0],temp[1],temp[2]);
			break;
	    case 4://Ԑ4ٶӎ˽
			res=(*(uint32_t(*)())usmart_dev.funs[id].func)(temp[0],temp[1],temp[2],temp[3]);
			break;
	    case 5://Ԑ5ٶӎ˽
			res=(*(uint32_t(*)())usmart_dev.funs[id].func)(temp[0],temp[1],temp[2],temp[3],temp[4]);
			break;
	    case 6://Ԑ6ٶӎ˽
			res=(*(uint32_t(*)())usmart_dev.funs[id].func)(temp[0],temp[1],temp[2],temp[3],temp[4],\
			temp[5]);
			break;
	    case 7://Ԑ7ٶӎ˽
			res=(*(uint32_t(*)())usmart_dev.funs[id].func)(temp[0],temp[1],temp[2],temp[3],temp[4],\
			temp[5],temp[6]);
			break;
	    case 8://Ԑ8ٶӎ˽
			res=(*(uint32_t(*)())usmart_dev.funs[id].func)(temp[0],temp[1],temp[2],temp[3],temp[4],\
			temp[5],temp[6],temp[7]);
			break;
	    case 9://Ԑ9ٶӎ˽
			res=(*(uint32_t(*)())usmart_dev.funs[id].func)(temp[0],temp[1],temp[2],temp[3],temp[4],\
			temp[5],temp[6],temp[7],temp[8]);
			break;
	    case 10://Ԑ10ٶӎ˽
			res=(*(uint32_t(*)())usmart_dev.funs[id].func)(temp[0],temp[1],temp[2],temp[3],temp[4],\
			temp[5],temp[6],temp[7],temp[8],temp[9]);
			break;
	}
	usmart_get_runtime();//ܱȡگ˽ִѐʱݤ
	if(rval==1)//ѨҪ׵ܘֵ.
	{
//		if(usmart_dev.sptype==SP_TYPE_DEC)//printf("=%lu;\r\n",res);//ˤԶִѐޡڻ(10޸׆ӎ˽Дʾ)
//		else //printf("=0X%X;\r\n",res);//ˤԶִѐޡڻ(16޸׆ӎ˽Дʾ)	   
	}else //printf(";\r\n");		//һѨҪ׵ܘֵ,ֱޓˤԶޡ˸
	if(usmart_dev.runtimeflag)	//ѨҪДʾگ˽ִѐʱݤ
	{ 
		//printf("Function Run Time:%d.%1dms\r\n",usmart_dev.runtime/10,usmart_dev.runtime%10);//ղӡگ˽ִѐʱݤ 
	}	
}
//usmartɨĨگ˽
//ͨڽַԃكگ˽,ʵЖusmartքٷٶ࠘׆.كگ˽ѨҪÿٴһ֨ʱݤѻַԃһՎ
//ӔܰʱִѐՓԮࠚעڽ4քٷٶگ˽.
//Ѿگ˽ࠉӔ՚א׏oĦַԃ,Փ׸ʵЖؔ֯ڜm.
//ɧڻ؇ALIENTEKԃۧ,ղUSART_RX_STAۍUSART_RX_BUF[]ѨҪԃۧؔܺʵЖ
//void usmart_scan(void)
//{
//	uint8_t sta,len;  
//	if(USART_RX_STA&0x8000)//Ԯࠚޓ˕Ϊԉÿ
//	{					   
//		len=USART_RX_STA&0x3fff;	//փսՋՎޓ˕սք˽ߝӤ׈
//		USART_RX_BUF[len]='\0';	//՚ĩβݓɫޡ˸ػ. 
//		sta=usmart_dev.cmd_rec(USART_RX_BUF);//փսگ˽ٷٶхϢ
//		if(sta==0)usmart_dev.exe();	//ִѐگ˽ 
//		else 
//		{  
//			len=usmart_sys_cmd_exe(USART_RX_BUF);
//			if(len!=USMART_FUNCERR)sta=len;
//			if(sta)
//			{
//				switch(sta)
//				{
//					case USMART_FUNCERR:
//						//printf("گ˽խϳ!\r\n");   			
//						break;	
//					case USMART_PARMERR:
//						//printf("ӎ˽խϳ!\r\n");   			
//						break;				
//					case USMART_PARMOVER:
//						//printf("ӎ˽̫נ!\r\n");   			
//						break;		
//					case USMART_NOFUNCFIND:
//						//printf("δ֒սƥƤքگ˽!\r\n");   			
//						break;		
//				}
//			}
//		}
//		USART_RX_STA=0;//״̬݄զǷȥࠕ	    
//	}
//}

#if USMART_USE_WRFUNS==1 	//ɧڻʹŜׁдәط
//ׁȡַָ֨֘քֵ		 
uint32_t read_addr(uint32_t addr)
{
	return *(uint32_t*)addr;//	
}
//՚ַָ֨֘дɫָ֨քֵ		 
void write_addr(uint32_t addr,uint32_t val)
{
	*(uint32_t*)addr=val; 	
}
#endif


