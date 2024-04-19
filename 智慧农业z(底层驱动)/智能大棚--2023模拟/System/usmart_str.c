#include "usmart_str.h"
#include "usmart.h"		   
//////////////////////////////////////////////////////////////////////////////////	 
//ѾԌѲֻ٩ѧϰʹԃìδޭط֟ѭࠉìһփԃԚǤ̼Ɏێԃ;
//ALIENTEK STM32ߪעѥ	   
//ֽ֣ԭؓ@ALIENTEK
//ܼ˵Û̳:www.openedv.com 
//ѦѾúV3.1
//ѦȨ̹ԐìցѦҘ޿c
//Copyright(C) ֽ֣ԭؓ 2011-2021
//All rights reserved
//********************************************************************************
//ʽܶ˵ķ
//V1.4
//նݓהӎ˽Ϊstring`эքگ˽ք֧Ԗ.ˊԃ׶Χճճٟ͡.
//ԅۯŚզռԃ,޲̬ŚզռԃΪ79ٶؖޚ@10ٶӎ˽.̬֯ˊӦ˽ؖܰؖػԮӤ׈
//V2.0 
//1,ўلlistָ®,ղӡگ˽քΪֻҭկʽ.
//2,նݓidָ®,ղӡÿٶگ˽քɫࠚַ֘.
//3,ўلӎ˽ƥƤ,֧Ԗگ˽ӎ˽քַԃ(ˤɫɫࠚַ֘).
//4,նݓگ˽ĻӤ׈۪֨ӥ.	
//V2.1 20110707		 
//1,նݓdec,hex}ٶָ®,ԃԚʨ׃ӎ˽Дʾ޸׆,ִܰѐ޸׆תۻ.
//ע:ձdec,hexһոӎ˽քʱ۲,ܴʨ֨Дʾӎ˽޸׆.ձ۳ٺӎ˽քʱ۲,ִܴѐ޸׆תۻ.
//ɧ:"dec 0XFF" ղܡݫ0XFFתΪ255,ԉԮࠚ׵ܘ.
//ɧ:"hex 100" 	ղܡݫ100תΪ0X64,ԉԮࠚ׵ܘ
//2,тնusmart_get_cmdnameگ˽,ԃԚܱȡָ®Ļؖ.
//V2.2 20110726	
//1,ўֽvoid`эӎ˽քӎ˽ͳ݆խϳ.
//2,ўل˽ߝДʾٱʽĬɏΪ16޸׆.
//V2.3 20110815
//1,ȥִگ˽Ļ۳Ҙѫٺ"("քО׆.
//2,ўֽؖػԮӎ˽אһŜԐ"("քbug.
//3,ўلگ˽ĬɏДʾӎ˽ٱʽքўل׽ʽ. 
//V2.4 20110905
//1,ўلusmart_get_cmdnameگ˽,նݓخճӎ˽Ӥ׈О׆.ҜĢˤɫխϳӎ˽ʱք̀ܺЖг.
//2,նݓUSMART_ENTIM2_SCAN۪֨ӥ,ԃԚƤ׃ˇرʹԃTIM2֨ʱִѐscanگ˽.
//V2.5 20110930
//1,ўلusmart_initگ˽Ϊvoid usmart_init(uint8_t sysclk),ࠉӔٹߝϵͳƵÊؔ֯ʨ֨ɨĨʱݤ.(ڌ֨100ms)
//2,ȥִusmart_initگ˽אքuart_initگ˽,ԮࠚԵʼۯҘѫ՚΢ҿԵʼۯ,׽ңԃۧؔѐڜm.
//V2.6 20111009
//1,նݓread_addrۍwrite_addr}ٶگ˽.ࠉӔ{ԃ֢}ٶگ˽ׁдŚҿɎӢַ֘(ҘѫˇԐЧַ֘).ټݓ׽ңַ˔.
//2,read_addrۍwrite_addr}ٶگ˽ࠉӔͨڽʨ׃USMART_USE_WRFUNSΪ4ʹŜۍژҕ.
//3,ўلusmart_strcmp,ʹǤڦ׶ۯ.			  
//V2.7 20111024
//1,ўֽ׵ܘֵ16޸׆Дʾʱһۻѐքbug.
//2,նݓگ˽ˇرԐ׵ܘֵքƐ׏,ɧڻûԐ׵ܘֵ,ղһܡДʾ.Ԑ׵ܘֵʱӅДʾǤ׵ܘֵ.
//V2.8 20111116
//1,ўֽlistֈһոӎ˽քָ®ע̍۳ࠉŜռׂ̀ܺքbug.
//V2.9 20120917
//1,ўلюɧúvoid*xxx(void)`эگ˽һŜʶҰքbugc
//V3.0 20130425
//1,тնؖػԮӎ˽התӥػք֧Ԗc
//V3.1 20131120
//1,նݓruntimeϵͳָ®,ࠉӔԃԚͳ݆گ˽ִѐʱݤ.
//ԃר:
//ע̍:runtime 1 ,ղߪǴگ˽ִѐʱݤͳ݆٦Ŝ
//ע̍:runtime 0 ,ղژҕگ˽ִѐʱݤͳ݆٦Ŝ
///runtimeͳ݆٦Ŝ,Ҙѫʨ׃:USMART_ENTIMX_SCAN Ϊ1,ӅࠉӔʹԃ!!
/////////////////////////////////////////////////////////////////////////////////////
  
//ה҈ؖػԮstr1ۍstr2
//*str1:ؖػԮ1ָ֫
//*str2:ؖػԮ2ָ֫
//׵ܘֵ:0ìРֈ;1ìһРֈ;
uint8_t usmart_strcmp(uint8_t *str1,uint8_t *str2)
{
	while(1)
	{
		if(*str1!=*str2)return 1;//һРֈ
		if(*str1=='\0')break;//ה҈Ϊԉ.
		str1++;
		str2++;
	}
	return 0;//}ٶؖػԮРֈ
}
//ёstr1քŚɝcopyսstr2
//*str1:ؖػԮ1ָ֫
//*str2:ؖػԮ2ָ֫			   
void usmart_strcopy(uint8_t*str1,uint8_t *str2)
{
	while(1)
	{										   
		*str2=*str1;	//߽Ѵ
		if(*str1=='\0')break;//߽ѴΪԉ.
		str1++;
		str2++;
	}
}
//փսؖػԮքӤ׈(ؖޚ)
//*str:ؖػԮָ֫
//׵ܘֵ:ؖػԮքӤ׈		   
uint8_t usmart_strlen(uint8_t*str)
{
	uint8_t len=0;
	while(1)
	{							 
		if(*str=='\0')break;//߽ѴΪԉ.
		len++;
		str++;
	}
	return len;
}
//m^nگ˽
//׵ܘֵ:m^nՎ׽
uint32_t usmart_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}	    
//ёؖػԮתΪ˽ؖ
//֧Ԗ16޸׆תۻ,իˇ16޸׆ؖĸҘѫˇճдք,ȒٱʽΪӔ0Xߪͷք.
//һ֧Ԗغ˽ 
//*str:˽ؖؖػԮָ֫
//*res:תۻΪքޡڻզ؅ַ֘.
//׵ܘֵ:0ìԉ٦תۻΪԉ.Ǥ̻,խϳպë.
//1,˽ߝٱʽխϳ.2,16޸׆λ˽Ϊ0.3,ǰʼٱʽխϳ.4,ʮ޸׆λ˽Ϊ0.
uint8_t usmart_str2num(uint8_t*str,uint32_t *res)
{
	uint32_t t;
	uint8_t bnum=0;	//˽ؖքλ˽
	uint8_t *p;		  
	uint8_t hexdec=10;//ĬɏΪʮ޸׆˽ߝ
	p=str;
	*res=0;//ȥ£.
	while(1)
	{
		if((*p<='9'&&*p>='0')||(*p<='F'&&*p>='A')||(*p=='X'&&bnum==1))//ӎ˽ۏר
		{
			if(*p>='A')hexdec=16;	//ؖػԮאզ՚ؖĸ,Ϊ16޸׆ٱʽ.
			bnum++;					//λ˽նݓ.
		}else if(*p=='\0')break;	//ƶսޡ˸ػ,΋Զ.
		else return 1;				//һȫˇʮ޸׆ܲ֟16޸׆˽ߝ.
		p++; 
	} 
	p=str;			    //טт֨λսؖػԮߪʼքַ֘.
	if(hexdec==16)		//16޸׆˽ߝ
	{
		if(bnum<3)return 2;			//λ˽СԚ3ìֱޓ΋Զ.ӲΪ0Xߍռ2ٶ,ɧڻ0X۳Ħһٺ˽ߝ,ղك˽ߝ؇ר.
		if(*p=='0' && (*(p+1)=='X'))//ҘѫӔ'0X'ߪͷ.
		{
			p+=2;	//ƫӆս˽ߝǰʼַ֘.
			bnum-=2;//ݵȥƫӆ	 
		}else return 3;//ǰʼͷքٱʽһה
	}else if(bnum==0)return 4;//λ˽Ϊ0ìֱޓ΋Զ.	  
	while(1)
	{
		if(bnum)bnum--;
		if(*p<='9'&&*p>='0')t=*p-'0';	//փս˽ؖքֵ
		else t=*p-'A'+10;				//փսA~FהӦքֵ	    
		*res+=t*usmart_pow(hexdec,bnum);		   
		p++;
		if(*p=='\0')break;//˽ߝּөΪ.	
	}
	return 0;//ԉ٦תۻ
}
//փսָ®Ļ
//*str:ԴؖػԮ
//*cmdname:ָ®Ļ
//*nlen:ָ®ĻӤ׈		
//maxlen:خճӤ׈(ضО׆,ָ®һࠉŜ̫Ӥք)	
//׵ܘֵ:0,ԉ٦;Ǥ̻,ʧќ.	  
uint8_t usmart_get_cmdname(uint8_t*str,uint8_t*cmdname,uint8_t *nlen,uint8_t maxlen)
{
	*nlen=0;
 	while(*str!=' '&&*str!='\0') //֒սࠕٱܲ֟ޡ˸ػղɏΪޡ˸
	{
		*cmdname=*str;
		str++;
		cmdname++;
		(*nlen)++;//ͳ݆ļ®Ӥ׈
		if(*nlen>=maxlen)return 1;//խϳքָ®
	}
	*cmdname='\0';//ݓɫޡ˸ػ
	return 0;//ֽӣ׵ܘ
}
//ܱȡЂһٶؖػèձאݤԐۜנࠕٱքʱ۲ìՋگ˽ֱޓ۶Ôࠕٱì֒սࠕٱ֮۳ք֚һٶؖػé
//str:ؖػԮָ֫	
//׵ܘֵ:Ђһٶؖػ
uint8_t usmart_search_nextc(uint8_t* str)
{		   	 	
	str++;
	while(*str==' '&&str!='\0')str++;
	return *str;
} 
//Փstrאփսگ˽Ļ
//*str:ԴؖػԮָ֫
//*fname:ܱȡսքگ˽Ļָؖ֫
//*pnum:گ˽քӎ˽ٶ˽
//*rval:ˇرѨҪДʾ׵ܘֵ(0,һѨҪ;1,ѨҪ)
//׵ܘֵ:0,ԉ٦;Ǥ̻,խϳպë.
uint8_t usmart_get_fname(uint8_t*str,uint8_t*fname,uint8_t *pnum,uint8_t *rval)
{
	uint8_t res;
	uint8_t fover=0;	  //(ۅʮ׈
	uint8_t *strtemp;
	uint8_t offset=0;  
	uint8_t parmnum=0;
	uint8_t temp=1;
	uint8_t fpname[6];//void+X+'/0'
	uint8_t fplcnt=0; //֚һٶӎ˽քӤ׈݆˽Ƿ
	uint8_t pcnt=0;	 //ӎ˽݆˽Ƿ
	uint8_t nchar;
	//Ɛ׏گ˽ˇرԐ׵ܘֵ
	strtemp=str;
	while(*strtemp!='\0')//ûԐޡ˸
	{
		if(*strtemp!=' '&&(pcnt&0X7F)<5)//خנ݇¼5ٶؖػ
		{	
			if(pcnt==0)pcnt|=0X80;//׃λخٟλ,Ҫ݇ߪʼޓ˕׵ܘֵ`э
			if(((pcnt&0x7f)==4)&&(*strtemp!='*'))break;//خ۳һٶؖػ,Ҙѫˇ*
			fpname[pcnt&0x7f]=*strtemp;//݇¼گ˽ք׵ܘֵ`э
			pcnt++;
		}else if(pcnt==0X85)break;
		strtemp++; 
	} 
	if(pcnt)//ޓ˕Ϊ
	{
		fpname[pcnt&0x7f]='\0';//ݓɫޡ˸ػ
		if(usmart_strcmp(fpname,"void")==0)*rval=0;//һѨҪ׵ܘֵ
		else *rval=1;							   //ѨҪ׵ܘֵ
		pcnt=0;
	} 
	res=0;
	strtemp=str;
	while(*strtemp!='('&&*strtemp!='\0') //Ջպë֒սگ˽Ļքֽ֦ǰʼλ׃
	{  
		strtemp++;
		res++;
		if(*strtemp==' '||*strtemp=='*')
		{
			nchar=usmart_search_nextc(strtemp);		//ܱȡЂһٶؖػ
			if(nchar!='('&&nchar!='*')offset=res;	//͸ڽࠕٱۍ*ۅ
		}
	}	 
	strtemp=str;
	if(offset)strtemp+=offset+1;//͸սگ˽Ļߪʼք֘׽	   
	res=0;
	nchar=0;//ˇرֽ՚ؖػԮoĦքҪ־,0ìһ՚ؖػԮ;1ì՚ؖػԮ;
	while(1)
	{
		if(*strtemp==0)
		{
			res=USMART_FUNCERR;//گ˽խϳ
			break;
		}else if(*strtemp=='('&&nchar==0)fover++;//(ۅʮ׈նݓһܶ	 
		else if(*strtemp==')'&&nchar==0)
		{
			if(fover)fover--;
			else res=USMART_FUNCERR;//խϳޡ˸,û˕ս'('
			if(fover==0)break;//սĩβ,΋Զ	    
		}else if(*strtemp=='"')nchar=!nchar;

		if(fover==0)//گ˽Ļ۹ûޓ˕Ϊ
		{
			if(*strtemp!=' ')//ࠕٱһ˴Ԛگ˽Ļ
			{
				*fname=*strtemp;//փսگ˽Ļ
				fname++;
			}
		}else //ӑޭޓ˜Ϊگ˽Ļ.
		{
			if(*strtemp==',')
			{
				temp=1;		//ʹŜնݓһٶӎ˽
				pcnt++;	
			}else if(*strtemp!=' '&&*strtemp!='(')
			{
				if(pcnt==0&&fplcnt<5)		//ձ֚һٶӎ˽4ʱ,ΪҜĢͳ݆void`эքӎ˽,ҘѫضƐ׏.
				{
					fpname[fplcnt]=*strtemp;//݇¼ӎ˽ַ͘.
					fplcnt++;
				}
				temp++;	//փսԐЧӎ˽(؇ࠕٱ)
			}
			if(fover==1&&temp==2)
			{
				temp++;		//؀ֹטشնݓ
				parmnum++; 	//ӎ˽նݓһٶ
			}
		}
		strtemp++; 			
	}   
	if(parmnum==1)//ֻԐ1ٶӎ˽.
	{
		fpname[fplcnt]='\0';//ݓɫޡ˸ػ
		if(usmart_strcmp(fpname,"void")==0)parmnum=0;//ӎ˽Ϊvoid,ҭʾûԐӎ˽.
	}
	*pnum=parmnum;	//݇¼ӎ˽ٶ˽
	*fname='\0';	//ݓɫޡ˸ػ
	return res;		//׵ܘִѐޡڻ
}


//Փstrאփսһٶگ˽քӎ˽
//*str:ԴؖػԮָ֫
//*fparm:ӎ˽ؖػԮָ֫
//*ptype:ӎ˽`э 0ì˽ؖ;1ìؖػԮ;0XFFìӎ˽խϳ
//׵ܘֵ:0,ӑޭϞӎ˽;Ǥ̻,Ђһٶӎ˽քƫӆ.
uint8_t usmart_get_aparm(uint8_t *str,uint8_t *fparm,uint8_t *ptype)
{
	uint8_t i=0;
	uint8_t enout=0;
	uint8_t type=0;//Ĭɏˇ˽ؖ
	uint8_t string=0; //Ҫ݇strˇرֽ՚ׁ
	while(1)
	{		    
		if(*str==','&& string==0)enout=1;			//՝ۺbܴ΋Զ,ĿքˇѰ֒Ђһٶӎ˽քǰʼַ֘
		if((*str==')'||*str=='\0')&&string==0)break;//bܴ΋ԶҪʶػ
		if(type==0)//Ĭɏˇ˽ؖք
		{
			if((*str>='0' && *str<='9')||(*str>='a' && *str<='f')||(*str>='A' && *str<='F')||*str=='X'||*str=='x')//˽ؖԮݬӢ
			{
				if(enout)break;					//֒սЂһٶӎ˽,ֱޓ΋Զ.
				if(*str>='a')*fparm=*str-0X20;	//СдתۻΪճд
				else *fparm=*str;		   		//Сдܲ֟˽ؖѣԖһҤ
				fparm++;
			}else if(*str=='"')//֒սؖػԮքߪʼҪ־
			{
				if(enout)break;//֒ս,۳Ӆ֒ս",ɏΪޡ˸.
				type=1;
				string=1;//և݇STRING ֽ՚ׁ
			}else if(*str!=' '&&*str!=',')//עЖ؇רؖػ,ӎ˽խϳ
			{
				type=0XFF;
				break;
			}
		}else//string`
		{ 
			if(*str=='"')string=0;
			if(enout)break;			//֒սЂһٶӎ˽,ֱޓ΋Զ.
			if(string)				//ؖػԮֽ՚ׁ
			{	
				if(*str=='\\')		//Զսתӥػ(һش׆תӥػ)
				{ 
					str++;			//ƫӆսתӥػ۳Ħքؖػ,һڜʲôؖػ,ֱޓCOPY
					i++;
				}					
				*fparm=*str;		//Сдܲ֟˽ؖѣԖһҤ
				fparm++;
			}	
		}
		i++;//ƫӆնݓ
		str++;
	}
	*fparm='\0';	//ݓɫޡ˸ػ
	*ptype=type;	//׵ܘӎ˽`э
	return i;		//׵ܘӎ˽Ӥ׈
}
//փսָ֨ӎ˽քǰʼַ֘
//num:֚numٶӎ˽,׶Χ0~9.
//׵ܘֵ:كӎ˽քǰʼַ֘
uint8_t usmart_get_parmpos(uint8_t num)
{
	uint8_t temp=0;
	uint8_t i;
	for(i=0;i<num;i++)temp+=usmart_dev.plentbl[i];
	return temp;
}
//Փstrאփսگ˽ӎ˽
//str:ԴؖػԮ;
//parn:ӎ˽քנʙ.0ҭʾϞӎ˽ void`э
//׵ܘֵ:0,ԉ٦;Ǥ̻,խϳպë.
uint8_t usmart_get_fparam(uint8_t*str,uint8_t *parn)
{	
	uint8_t i,type;  
	uint32_t res;
	uint8_t n=0;
	uint8_t len;
	uint8_t tstr[PARM_LEN+1];//ؖޚӤ׈քۺզ,خנࠉӔզ؅PARM_LENٶؖػքؖػԮ
	for(i=0;i<MAX_PARM;i++)usmart_dev.plentbl[i]=0;//ȥࠕӎ˽Ӥ׈ҭ
	while(*str!='(')//ƫӆսӎ˽ߪʼք֘׽
	{
		str++;											    
		if(*str=='\0')return USMART_FUNCERR;//Զսޡ˸ػ
	}
	str++;//ƫӆս"("֮۳ք֚һٶؖޚ
	while(1)
	{
		i=usmart_get_aparm(str,tstr,&type);	//փս֚һٶӎ˽  
		str+=i;								//ƫӆ
		switch(type)
		{
			case 0:	//˽ؖ
				if(tstr[0]!='\0')				//ޓ˕սքӎ˽ԐЧ
				{					    
					i=usmart_str2num(tstr,&res);	//݇¼كӎ˽	 
					if(i)return USMART_PARMERR;		//ӎ˽խϳ.
					*(uint32_t*)(usmart_dev.parm+usmart_get_parmpos(n))=res;//݇¼תۻԉ٦քޡڻ.
					usmart_dev.parmtype&=~(1<<n);	//Ҫ݇˽ؖ
					usmart_dev.plentbl[n]=4;		//كӎ˽քӤ׈Ϊ4  
					n++;							//ӎ˽նݓ  
					if(n>MAX_PARM)return USMART_PARMOVER;//ӎ˽̫נ
				}
				break;
			case 1://ؖػԮ	 	
				len=usmart_strlen(tstr)+1;	//Ѽڬޡ˸ػ'\0'
				usmart_strcopy(tstr,&usmart_dev.parm[usmart_get_parmpos(n)]);//߽Ѵtstr˽ߝսusmart_dev.parm[n]
				usmart_dev.parmtype|=1<<n;	//Ҫ݇ؖػԮ 
				usmart_dev.plentbl[n]=len;	//كӎ˽քӤ׈Ϊlen  
				n++;
				if(n>MAX_PARM)return USMART_PARMOVER;//ӎ˽̫נ
				break;
			case 0XFF://խϳ
				return USMART_PARMERR;//ӎ˽խϳ	  
		}
		if(*str==')'||*str=='\0')break;//өսޡ˸Ҫ־.
	}
	*parn=n;	//݇¼ӎ˽քٶ˽
	return USMART_OK;//ֽȷփսӎ˽
}
