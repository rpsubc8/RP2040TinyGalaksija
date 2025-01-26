#ifndef _GB_GTP_H
 #define _GB_GTP_H

 #include "gbCompileDataOpt.h"

 //#include <stddef.h>
 #ifdef gb_use_lib_compile_arduinodroid
  #include "gtpAsteroidiGACSoftware.h"
  #include "gtpBiljar.h"
  #include "gtpBladeAlleyHalilovicJasmin.h"
  #include "gtpBombarderBalintNenad.h"
  #include "gtpComets.h"
  #include "gtpDijamantskiRudnikBalintNenad.h"
  #include "gtpEgemond.h"
  #include "gtpFormula1.h"
  #include "gtpFourVujkovDragan.h"
  #include "gtpGalaktickiRatVojaAntonic.h"
  #include "gtpHungryHorace.h"
  #include "gtpIgraDiskovaMihailovicVojislav.h"
  #include "gtpJumpingJackVojaAntonic.h"
  #include "gtpLightCycles2.h"
  #include "gtpLightCyclesStanojevic.h"
  #include "gtpManicMiner.h"
  #include "gtpMastermajndRistanovicDejan.h"
  #include "gtpMastermind.h"
  #include "gtpMaze.h"
  #include "gtpMemorija.h"
  #include "gtpNightPilotVukoticDragutin.h"
  #include "gtpPamtiliceMilosavljevicPeca.h"
  #include "gtpPokerBalintNenad.h"
  #include "gtpRainDrops.h"
  #include "gtpScater.h"
  #include "gtpSlalom2GerovacZeljko.h"
  #include "gtpSnake2VujkovDragan.h"
  #include "gtpSnakeBalintNenad.h"
  #include "gtpSquash.h"
  #include "gtpSuperCruiserHalilovicJasmin.h"
//  #include "gtpSuperSahPageSoftware.h"
  #include "gtpSvemirskiTrgovacVitanovIlija.h"
  #include "gtpTenis3VujkovDragan.h"
  #include "gtpTenisBalintNenad.h"
  #include "gtpTetrisObradovicDragoljub.h"
  #include "gtpWallVujkovDragan.h"
  #include "gtpWonderer.h"
  #include "gtpWonderer2.h"
  #include "gtpZamakVojaAntonic.h"
  #include "gtpZidGACSoftware.h"
  #include "gtpZiulRistanovicDejan.h"
  #include "gtpZvezdice.h"
  #include "gtpZvjezdaneStaze.h"

  //DEMOS 3 BEGIN
  #include "gtpDemowin11check.h"
  #include "gtpDemoHalloween.h"
  #include "gtpDemoretroinfo.h"
  //DEMOS 3 END

  //DEMOS BEGIN 8
  #include "gtpDemoStarsSolcTomaz.h"
  #include "gtpDemoBioritam1984.h"
  #include "gtpDemoBioritam219xx.h" 
  #include "gtpDemoEvolucija19840331.h"
  #include "gtpDemoFireSolcTomaz.h"   
  #include "gtpDemoLightShow1987.h"
  #include "gtpDemoOscilacije19xx.h"
  #include "gtpDemoParticleSolcTomaz.h"
 //DEMOS 8 END  
 #else
  #include "gtp/gtpAsteroidiGACSoftware.h"
  #include "gtp/gtpBiljar.h"
  #include "gtp/gtpBladeAlleyHalilovicJasmin.h"
  #include "gtp/gtpBombarderBalintNenad.h"
  #include "gtp/gtpComets.h"
  #include "gtp/gtpDijamantskiRudnikBalintNenad.h"
  #include "gtp/gtpEgemond.h"
  #include "gtp/gtpFormula1.h"
  #include "gtp/gtpFourVujkovDragan.h"
  #include "gtp/gtpGalaktickiRatVojaAntonic.h"
  #include "gtp/gtpHungryHorace.h"
  #include "gtp/gtpIgraDiskovaMihailovicVojislav.h"
  #include "gtp/gtpJumpingJackVojaAntonic.h"
  #include "gtp/gtpLightCycles2.h"
  #include "gtp/gtpLightCyclesStanojevic.h"
  #include "gtp/gtpManicMiner.h"
  #include "gtp/gtpMastermajndRistanovicDejan.h"
  #include "gtp/gtpMastermind.h"
  #include "gtp/gtpMaze.h"
  #include "gtp/gtpMemorija.h"
  #include "gtp/gtpNightPilotVukoticDragutin.h"
  #include "gtp/gtpPamtiliceMilosavljevicPeca.h"
  #include "gtp/gtpPokerBalintNenad.h"
  #include "gtp/gtpRainDrops.h"
  #include "gtp/gtpScater.h"
  #include "gtp/gtpSlalom2GerovacZeljko.h"
  #include "gtp/gtpSnake2VujkovDragan.h"
  #include "gtp/gtpSnakeBalintNenad.h"
  #include "gtp/gtpSquash.h"
  #include "gtp/gtpSuperCruiserHalilovicJasmin.h"
//  #include "gtp/gtpSuperSahPageSoftware.h"
  #include "gtp/gtpSvemirskiTrgovacVitanovIlija.h"
  #include "gtp/gtpTenis3VujkovDragan.h"
  #include "gtp/gtpTenisBalintNenad.h"
  #include "gtp/gtpTetrisObradovicDragoljub.h"
  #include "gtp/gtpWallVujkovDragan.h"
  #include "gtp/gtpWonderer.h"
  #include "gtp/gtpWonderer2.h"
  #include "gtp/gtpZamakVojaAntonic.h"
  #include "gtp/gtpZidGACSoftware.h"
  #include "gtp/gtpZiulRistanovicDejan.h"
  #include "gtp/gtpZvezdice.h"
  #include "gtp/gtpZvjezdaneStaze.h"
  
  //DEMOS 3 BEGIN
  #include "gtp/gtpDemowin11check.h"
  #include "gtp/gtpDemoHalloween.h"
  #include "gtp/gtpDemoretroinfo.h"
  //DEMOS 3 END
  
 //DEMOS BEGIN 8
 #include "gtp/gtpDemoStarsSolcTomaz.h"
 #include "gtp/gtpDemoBioritam1984.h"
 #include "gtp/gtpDemoBioritam219xx.h" 
 #include "gtp/gtpDemoEvolucija19840331.h"
 #include "gtp/gtpDemoFireSolcTomaz.h"  
 #include "gtp/gtpDemoLightShow1987.h"
 #include "gtp/gtpDemoOscilacije19xx.h"
 #include "gtp/gtpDemoParticleSolcTomaz.h"
 //DEMOS 8 END
 #endif 



 //#define max_list_gtp 43
 //#define max_list_gtp 42
 //42 + 3 DEMOS + 8 DEMOS
 #define max_list_gtp 53
 
 //gtp
 //Titulos
 static const char * gb_list_gtp_title[max_list_gtp]={
  "Asteroidi GAC Software",
  "Biljar",
  "Blade Alley Halilovic Jasmin",
  "Bombarder Balint Nenad",
  "Comets",
  "Dijamantski Rudnik Balint Nenad",
  "Egemond",
  "Formula1",
  "Four Vujkov Dragan",
  "Galakticki Rat Voja Antonic",
  "Hungry Horace",
  "Igra Diskova Mihailovic Vojislav",
  "Jumping Jack Voja Antonic",
  "Light Cycles 2",
  "Light Cycles Stanojevic",
  "Manic Miner",
  "Mastermajnd Ristanovic Dejan",
  "Mastermind",
  "Maze",
  "Memorija",
  "Night Pilot Vukotic Dragutin",
  "Pamtilice Milosavljevic Peca",
  "Poker Balint Nenad",
  "Rain Drops",
  "Scater",
  "Slalom 2 Gerovac Zeljko",
  "Snake 2 Vujkov Dragan",
  "Snake Balint Nenad",
  "Squash",
  "Super Cruiser Hallovic Jasmin",
//  "Super Sah Page Software",
  "Svemirski Trgova Vitanov Ilija",
  "Tenis 3 Vujkov Dragan",
  "Tenis Balint Nenad",
  "Tetris Obradovic Dragoljub",
  "Wall Vujkov Dragan",
  "Wonderer",
  "Wonderer 2",
  "Zamak Voja Antonic",
  "Zid GAC Software",
  "Ziul Ristanovic Dejan",
  "Zvez dice",
  "Zvjez dane Staze",
  
  //DEMOS 3 BEGIN
  "Demo win11check",  
  "Demo Halloween",  
  "Demo retroinfo",  
  //DEMOS 3 END
  
  //DEMOS 8 BEGIN
  "Demo Stars Solc Tomaz",
  "Demo Bioritam 1984",
  "Demo Bioritam 2 19xx",  
  "Demo Evolucija 1984 03 31",
  "Demo Fire Solc Tomaz",  
  "Demo Light Show 1987",
  "Demo Oscilacije 19xx",
  "Demo Particle Solc Tomaz"
  //DEMOS 8 END  
 };
 
 //Size bytes
 static const unsigned short int gb_list_gtp_size[max_list_gtp]={
  1298,
  1017,
  1879,
  1880,
  411,
  2754,
  2913,
  1194,
  2631,
  2238,
  797,
  1768,
  1891,
  1550,
  1245,
  4378,
  2077,
  1035,
  2530,
  2357,
  4854,
  3076,
  4424,
  573,
  1892,
  1328,
  1686,
  3173,
  1504,
  2569,
//  5773,
  2982,
  1874,
  2389,
  2709,
  1328,
  2863,
  1866,
  3015,
  2142,
  6673,
  1584,
  4950,
  
  //DEMOS 3 BEGIN
  782,  //win11check
  2175, //Halloween
  2477, //retroinfo
  //DEMOS 3 END
  
  //DEMOS 8 BEGIN
  573,   //DemoStarsSolcTomaz
  2996,  //DemoBioritam1984
  1366,  //DemoBioritam219xx
  1063,  //DemoEvolucija19840331
  772,   //DemoFireSolcTomaz
  3001,  //DemoLightShow1987
  504,   //DemoOscilacije19xx
  631    //DemoParticleSolcTomaz
  //DEMOS 8 END
 };
 
 
 //Data
 static const unsigned char * gb_list_gtp_data[max_list_gtp]={
  gb_gtp_data_AsteroidiGACSoftware,
  gb_gtp_data_Biljar,
  gb_gtp_data_BladeAlleyHalilovicJasmin,
  gb_gtp_data_BombarderBalintNenad,
  gb_gtp_data_Comets,
  gb_gtp_data_DijamantskiRudnikBalintNenad,
  gb_gtp_data_Egemond,
  gb_gtp_data_Formula1,
  gb_gtp_data_FourVujkovDragan,
  gb_gtp_data_GalaktickiRatVojaAntonic,
  gb_gtp_data_HungryHorace,
  gb_gtp_data_IgraDiskovaMihailovicVojislav,
  gb_gtp_data_JumpingJackVojaAntonic,
  gb_gtp_data_LightCycles2,
  gb_gtp_data_LightCyclesStanojevic,
  gb_gtp_data_ManicMiner,
  gb_gtp_data_MastermajndRistanovicDejan,
  gb_gtp_data_Mastermind,
  gb_gtp_data_Maze,
  gb_gtp_data_Memorija,
  gb_gtp_data_NightPilotVukoticDragutin,
  gb_gtp_data_PamtiliceMilosavljevicPeca,
  gb_gtp_data_PokerBalintNenad,
  gb_gtp_data_RainDrops,
  gb_gtp_data_Scater,
  gb_gtp_data_Slalom2GerovacZeljko,
  gb_gtp_data_Snake2VujkovDragan,
  gb_gtp_data_SnakeBalintNenad,
  gb_gtp_data_Squash,
  gb_gtp_data_SuperCruiserHalilovicJasmin,
//  gb_gtp_data_SuperSahPageSoftware,
  gb_gtp_data_SvemirskiTrgovacVitanovIlija,
  gb_gtp_data_Tenis3VujkovDragan,
  gb_gtp_data_TenisBalintNenad,
  gb_gtp_data_TetrisObradovicDragoljub,
  gb_gtp_data_WallVujkovDragan,
  gb_gtp_data_Wonderer,
  gb_gtp_data_Wonderer2,
  gb_gtp_data_ZamakVojaAntonic,
  gb_gtp_data_ZidGACSoftware,
  gb_gtp_data_ZiulRistanovicDejan,
  gb_gtp_data_Zvezdice,
  gb_gtp_data_ZvjezdaneStaze,

  //DEMOS BEGIN 3
  gb_gtp_data_Demo_win11check,  
  gb_gtp_data_Demo_Halloween,  
  gb_gtp_data_Demo_retroinfo,
  //DEMOS END 3
  
  //DEMOS BEGIN 8
  gb_gtp_data_Demo_Stars_Solc_Tomaz,
  gb_gtp_data_Demo_Bioritam_1984,
  gb_gtp_data_Demo_Bioritam_2_19xx,  
  gb_gtp_data_Demo_Evolucija_1984_03_31,
  gb_gtp_data_Demo_Fire_Solc_Tomaz,    
  gb_gtp_data_Demo_Light_Show_1987,
  gb_gtp_data_Demo_Oscilacije_19xx,
  gb_gtp_data_Demo_Particle_Solc_Tomaz  
  //DEMOS 8 END  
 };


#endif

