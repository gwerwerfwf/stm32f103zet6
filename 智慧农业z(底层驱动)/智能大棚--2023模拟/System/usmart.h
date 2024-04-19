#ifndef __USMART_H
#define __USMART_H	  		  
#include "usmart_str.h"

////////////////////////////////////////////ԃۧƤ׃ӎ˽////////////////////////////////////////////////////	  
#define MAX_FNAME_LEN 		30	//گ˽ĻخճӤ׈ìӦكʨ׃ΪһСԚخӤگ˽ĻքӤ׈c											   
#define MAX_PARM 			10	//خճΪ10ٶӎ˽ ,ўلՋӎ˽,Ҙѫўلusmart_exeԫ֮הӦ.
#define PARM_LEN 			200	//̹Ԑӎ˽֮ۍքӤ׈һӬڽPARM_LENٶؖޚ,עӢԮࠚޓ˕ҿؖҪԫ֮הӦ(һСԚPARM_LEN)


#define USMART_ENTIMX_SCAN 	1	//ʹԃTIMք֨ʱא׏4ɨĨSCANگ˽,ɧڻʨ׃Ϊ0,ѨҪؔܺʵЖٴһ׎ʱݤɨĨһՎscanگ˽.
								//עӢ:ɧڻҪԃruntimeͳ݆٦Ŝ,Ҙѫʨ׃USMART_ENTIMX_SCANΪ1!!!!
								
#define USMART_USE_HELP		1	//ʹԃѯ׺ìكֵʨΪ0ìࠉӔޚʡ޼700ٶؖޚìիˇݫռׂϞרДʾѯ׺хϢc
#define USMART_USE_WRFUNS	1	//ʹԃׁдگ˽,ʹŜ֢o,ࠉӔׁȡɎێַ֘քֵ,۹ࠉӔд݄զǷքֵ.
///////////////////////////////////////////////END///////////////////////////////////////////////////////////

#define USMART_OK 			0  //Ϟխϳ
#define USMART_FUNCERR 		1  //گ˽խϳ
#define USMART_PARMERR 		2  //ӎ˽խϳ
#define USMART_PARMOVER 	3  //ӎ˽ӧԶ
#define USMART_NOFUNCFIND 	4  //δ֒սƥƤگ˽

#define SP_TYPE_DEC      	0  //10޸׆ӎ˽Дʾ
#define SP_TYPE_HEX       	1  //16޸׆ӎ˽Дʾ


 //گ˽Ļҭ	 
struct _m_usmart_nametab
{
	void* func;			//گ˽ָ֫
	const uint8_t* name;		//گ˽Ļ(ө֒Ԯ)	 
};
//usmart࠘׆ڜmǷ
struct _m_usmart_dev
{
	struct _m_usmart_nametab *funs;	//گ˽Ļָ֫

	void (*init)(uint8_t);				//Եʼۯ
	uint8_t (*cmd_rec)(uint8_t*str);			//ʶҰگ˽Ļܰӎ˽
	void (*exe)(void); 				//ִѐ 
	void (*scan)(void);             //ɨĨ
	uint8_t fnum; 				  		//گ˽˽
	uint8_t pnum;                        //ӎ˽˽
	uint8_t id;							//گ˽id
	uint8_t sptype;						//ӎ˽Дʾ`э(؇ؖػԮӎ˽):0,10޸׆;1,16޸׆;
	uint16_t parmtype;					//ӎ˽ք`э
	uint8_t  plentbl[MAX_PARM];  		//ÿٶӎ˽քӤ׈՝զҭ
	uint8_t  parm[PARM_LEN];  			//گ˽քӎ˽
	uint8_t runtimeflag;					//0,һͳ݆گ˽ִѐʱݤ;1,ͳ݆گ˽ִѐʱݤ,עӢ:Ջ٦ŜҘѫ՚USMART_ENTIMX_SCANʹŜքʱ۲,ӅԐԃ
	uint32_t runtime;					//Ջѐʱݤ,եλ:0.1ms,خճғʱʱݤΪ֨ʱǷCNTֵք2Ѷ*0.1ms
};
extern struct _m_usmart_nametab usmart_nametab[];	//՚usmart_config.coĦ֨ӥ
extern struct _m_usmart_dev usmart_dev;				//՚usmart_config.coĦ֨ӥ


void usmart_init(uint8_t sysclk);//Եʼۯ
uint8_t usmart_cmd_rec(uint8_t*str);	//ʶҰ
void usmart_exe(void);		//ִѐ
void usmart_scan(void);     //ɨĨ
uint32_t read_addr(uint32_t addr);	//ׁȡַָ֨֘քֵ
void write_addr(uint32_t addr,uint32_t val);//՚ַָ֨֘дɫָ֨քֵ
uint32_t usmart_get_runtime(void);	//ܱȡՋѐʱݤ
void usmart_reset_runtime(void);//شλՋѐʱݤ

#endif
