#include "StdInc.h"

#include "AEPedSpeechAudioEntity.h"
#include "AEAudioUtility.h"
#include "PedClothesDesc.h"
#include <AEAudioHardware.h>
#include <Audio/eSoundBankSlot.h>

// Data from @ 0x8C6A68
// TIP: Disable word-wrap when viewing this array... :D
static constexpr std::array<tSpeechContextInfo, GCTX_NUM> gSpeechContextLookup{{
    // GCtx                                PED_TYPE_GEN                  PED_TYPE_EMG                  PED_TYPE_PLAYER               PED_TYPE_GANG                 PED_TYPE_GFD                     RepeatTime Zero
    {GCTX_NO_SPEECH,                      {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ABUSE_GANG_BALLAS,              {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_PHYS,          GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ABUSE_GANG_LSV,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_CLOTHES,       GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ABUSE_GANG_VLA,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_HAIR,          GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ABUSE_GANG_FAMILIES,            {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_CAR,           GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ABUSE_TRIAD,                    {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ABUSE_MAFIA,                    {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ABUSE_RIFA,                     {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ABUSE_DA_NANG,                  {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ACCEPT_DATE_CALL,               {GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_CRASH,               GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ACCEPT_DATE_REQUEST,            {GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_DRIVEBY_BURN_RUBBER, GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_AFTER_SEX,                      {GCTX_UNK,                     GCTX_UNK,                     GCTX_NO_SPEECH,               GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_APOLOGY,                        {GCTX_UNK,                     GCTX_UNK,                     GCTX_ABUSE_GANG_BALLAS,       GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ARREST,                         {GCTX_UNK,                     GCTX_BLOCKED,                 GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ARREST_CRIM,                    {GCTX_UNK,                     GCTX_BOOZE_RECEIVE,           GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ARRESTED,                       {GCTX_FOLLOW_CONSTANT,         GCTX_UNK,                     GCTX_ABUSE_GANG_LSV,          GCTX_NO_SPEECH,               GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ATTACK_BY_PLAYER_LIKE,          {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_SHOES,         GCTX_UNK,                     }, 5000,       0 },
    {GCTX_ATTACK_GANG_BALLAS,             {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_SMELL,         GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ATTACK_GANG_LSV,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_GAMB_BJ_SPLIT,           GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ATTACK_GANG_VLA,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_GAMB_CASINO_WIN,         GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ATTACK_PLAYER,                  {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CRASH_GENERIC,           GCTX_UNK,                     }, 7000,       0 },
    {GCTX_BAR_CHAT,                       {GCTX_BAR_CHAT,                GCTX_UNK,                     GCTX_UNK,                     GCTX_ABUSE_GANG_LSV,          GCTX_UNK,                     }, 20000,      0 },
    {GCTX_BLOCKED,                        {GCTX_ABUSE_GANG_VLA,          GCTX_BOOZE_REQUEST,           GCTX_UNK,                     GCTX_ABUSE_GANG_VLA,          GCTX_GAMB_BJ_HIT,             }, 7000,       0 },
    {GCTX_BOOZE_RECEIVE,                  {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_ABUSE_GANG_FAMILIES,     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_BOOZE_REQUEST,                  {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_ABUSE_TRIAD,             GCTX_UNK,                     }, 7000,       0 },
    {GCTX_BUM_BACK_OFF,                   {GCTX_EYEING_PED_THREAT,       GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_BUM_BACK_OFF_2,                 {GCTX_EYEING_PLAYER,           GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_BUM_LATCH,                      {GCTX_FIGHT,                   GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_BUMP,                           {GCTX_ABUSE_GANG_FAMILIES,     GCTX_BUM_BACK_OFF,            GCTX_UNK,                     GCTX_ABUSE_MAFIA,             GCTX_NO_SPEECH,               }, 7000,       0 },
    {GCTX_CAR_CRASH,                      {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_TATTOO,        GCTX_ABUSE_GANG_BALLAS,       }, 7000,       0 },
    {GCTX_CAR_DRIVEBY_BURN_RUBBER,        {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_EYEING_PED_THREAT,       GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CAR_DRIVEBY_TOO_FAST,           {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_EYEING_PLAYER,           GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CAR_FAST,                       {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_WEATHER,       GCTX_ABUSE_GANG_LSV,          }, 7000,       0 },
    {GCTX_CAR_FIRE,                       {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_IGNORED,            GCTX_ABUSE_GANG_VLA,          }, 7000,       0 },
    {GCTX_CAR_FLIPPED,                    {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_CAR,           GCTX_ABUSE_GANG_FAMILIES,     }, 7000,       0 },
    {GCTX_CAR_GET_IN,                     {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_FIGHT,                   GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CAR_HIT_PED,                    {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_CLOTHES,       GCTX_ABUSE_TRIAD,             }, 7000,       0 },
    {GCTX_CAR_JUMP,                       {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_HAIR,          GCTX_ABUSE_MAFIA,             }, 7000,       0 },
    {GCTX_CAR_POLICE_PURSUIT,             {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_PHYS,          GCTX_ABUSE_RIFA,              }, 15000,      0 },
    {GCTX_CAR_SLOW,                       {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_WEATHER,       GCTX_ABUSE_DA_NANG,           }, 7000,       0 },
    {GCTX_CAR_WAIT_FOR_ME,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_SHOES,         GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CAR_SINGALONG,                  {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CB_CHAT,                        {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 20000,      0 },
    {GCTX_CHASE_FOOT,                     {GCTX_UNK,                     GCTX_BUM_BACK_OFF_2,          GCTX_UNK,                     GCTX_ABUSE_DA_NANG,           GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CHASED,                         {GCTX_UNK,                     GCTX_UNK,                     GCTX_ABUSE_GANG_VLA,          GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CHAT,                           {GCTX_BLOCKED,                 GCTX_ABUSE_GANG_VLA,          GCTX_UNK,                     GCTX_ACCEPT_DATE_CALL,        GCTX_GAMB_BJ_LOSE,            }, 15000,      0 },
    {GCTX_COFFEE_ACCEPT,                  {GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_SINGALONG,           GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_COFFEE_DECLINE,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_CB_CHAT,                 GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CONV_DISL_CAR,                  {GCTX_DANCE_IMPR_NOT,          GCTX_UNK,                     GCTX_UNK,                     GCTX_CRIMINAL_PLEAD,          GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CONV_DISL_CLOTHES,              {GCTX_BOOZE_RECEIVE,           GCTX_UNK,                     GCTX_UNK,                     GCTX_DANCE_IMPR_HIGH,         GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CONV_DISL_HAIR,                 {GCTX_DANCE_IMPR_HIGH,         GCTX_UNK,                     GCTX_UNK,                     GCTX_GAMB_CASINO_LOSE,        GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CONV_DISL_PHYS,                 {GCTX_BOOZE_REQUEST,           GCTX_UNK,                     GCTX_UNK,                     GCTX_GANGBANG_NO,             GCTX_GAMB_BJ_STAY,            }, 7000,       0 },
    {GCTX_CONV_DISL_SHOES,                {GCTX_BUM_BACK_OFF,            GCTX_UNK,                     GCTX_UNK,                     GCTX_DANCE_IMPR_LOW,          GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CONV_DISL_SMELL,                {GCTX_CONV_LIKE_CLOTHES,       GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CONV_DISL_TATTOO,               {GCTX_CONV_LIKE_HAIR,          GCTX_UNK,                     GCTX_UNK,                     GCTX_GAMB_CONGRATS,           GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CONV_DISL_WEATHER,              {GCTX_CONV_LIKE_PHYS,          GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CONV_IGNORED,                   {GCTX_ABUSE_TRIAD,             GCTX_UNK,                     GCTX_UNK,                     GCTX_ACCEPT_DATE_REQUEST,     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CONV_LIKE_CAR,                  {GCTX_DODGE,                   GCTX_UNK,                     GCTX_UNK,                     GCTX_DANCE_IMPR_MED,          GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CONV_LIKE_CLOTHES,              {GCTX_BUM_BACK_OFF_2,          GCTX_UNK,                     GCTX_UNK,                     GCTX_DANCE_IMPR_NOT,          GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CONV_LIKE_HAIR,                 {GCTX_DANCE_IMPR_LOW,          GCTX_UNK,                     GCTX_UNK,                     GCTX_GAMB_ROUL_CHAT,          GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CONV_LIKE_PHYS,                 {GCTX_BUM_LATCH,               GCTX_UNK,                     GCTX_UNK,                     GCTX_GANGBANG_YES,            GCTX_GAMB_BJ_WIN,             }, 7000,       0 },
    {GCTX_CONV_LIKE_SHOES,                {GCTX_BUMP,                    GCTX_UNK,                     GCTX_UNK,                     GCTX_DODGE,                   GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CONV_LIKE_SMELL,                {GCTX_CONV_LIKE_SHOES,         GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CONV_LIKE_TATTOO,               {GCTX_CONV_LIKE_SMELL,         GCTX_UNK,                     GCTX_UNK,                     GCTX_GAMB_SLOT_WIN,           GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CONV_LIKE_WEATHER,              {GCTX_CONV_LIKE_TATTOO,        GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_COVER_ME,                       {GCTX_UNK,                     GCTX_ABUSE_GANG_FAMILIES,     GCTX_UNK,                     GCTX_AFTER_SEX,               GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CRASH_BIKE,                     {GCTX_CONV_LIKE_WEATHER,       GCTX_CAR_DRIVEBY_TOO_FAST,    GCTX_UNK,                     GCTX_APOLOGY,                 GCTX_GAMB_BJ_STICK,           }, 7000,       0 },
    {GCTX_CRASH_CAR,                      {GCTX_ABUSE_MAFIA,             GCTX_ARREST_CRIM,             GCTX_ABUSE_GANG_FAMILIES,     GCTX_ARREST,                  GCTX_GAMB_BJ_DOUBLE,          }, 7000,       0 },
    {GCTX_CRASH_GENERIC,                  {GCTX_ABUSE_RIFA,              GCTX_ARRESTED,                GCTX_ABUSE_TRIAD,             GCTX_ARREST_CRIM,             GCTX_GAMB_BJ_SPLIT,           }, 7000,       0 },
    {GCTX_CRIMINAL_PLEAD,                 {GCTX_DRUG_AGGRESSIVE_HIGH,    GCTX_UNK,                     GCTX_UNK,                     GCTX_ARRESTED,                GCTX_UNK,                     }, 7000,       0 },
    {GCTX_DANCE_IMPR_HIGH,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_DANCE_IMPR_LOW,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_DANCE_IMPR_MED,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_DANCE_IMPR_NOT,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_DODGE,                          {GCTX_ACCEPT_DATE_CALL,        GCTX_ABUSE_MAFIA,             GCTX_UNK,                     GCTX_ATTACK_BY_PLAYER_LIKE,   GCTX_ACCEPT_DATE_REQUEST,     }, 7000,       0 },
    {GCTX_DRUG_AGGRESSIVE_HIGH,           {GCTX_DRUGGED_CHAT,            GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_DRUG_AGGRESSIVE_LOW,            {GCTX_DRUGGED_IGNORE,          GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_DRUG_DEALER_DISLIKE,            {GCTX_UNK,                     GCTX_UNK,                     GCTX_ABUSE_MAFIA,             GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_DRUG_DEALER_HATE,               {GCTX_UNK,                     GCTX_UNK,                     GCTX_CRIMINAL_PLEAD,          GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_DRUG_REASONABLE_HIGH,           {GCTX_DRUGS_BUY,               GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_DRUG_REASONABLE_LOW,            {GCTX_DRUGS_SELL,              GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_DRUGGED_CHAT,                   {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_FOLLOW_ARRIVE,           GCTX_UNK,                     }, 20000,      0 },
    {GCTX_DRUGGED_IGNORE,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_FOLLOW_CONSTANT,         GCTX_UNK,                     }, 7000,       0 },
    {GCTX_DRUGS_BUY,                      {GCTX_COVER_ME,                GCTX_UNK,                     GCTX_UNK,                     GCTX_CHAT,                    GCTX_UNK,                     }, 7000,       0 },
    {GCTX_DRUGS_SELL,                     {GCTX_DUCK,                    GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_DUCK,                           {GCTX_UNK,                     GCTX_ABUSE_RIFA,              GCTX_UNK,                     GCTX_ATTACK_GANG_LSV,         GCTX_UNK,                     }, 7000,       0 },
    {GCTX_EYEING_PED,                     {GCTX_DANCE_IMPR_MED,          GCTX_UNK,                     GCTX_UNK,                     GCTX_ATTACK_PLAYER,           GCTX_UNK,                     }, 7000,       0 },
    {GCTX_EYEING_PED_THREAT,              {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_BAR_CHAT,                GCTX_UNK,                     }, 7000,       0 },
    {GCTX_EYEING_PLAYER,                  {GCTX_CAR_CRASH,               GCTX_UNK,                     GCTX_UNK,                     GCTX_GENERIC_HI_MALE,         GCTX_UNK,                     }, 7000,       0 },
    {GCTX_FIGHT,                          {GCTX_ACCEPT_DATE_REQUEST,     GCTX_ABUSE_DA_NANG,           GCTX_ABUSE_RIFA,              GCTX_BLOCKED,                 GCTX_AFTER_SEX,               }, 7000,       0 },
    {GCTX_FOLLOW_ARRIVE,                  {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_FOLLOW_REPLY,            GCTX_UNK,                     }, 15000,      0 },
    {GCTX_FOLLOW_CONSTANT,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_GAMB_BJ_HIT,             GCTX_UNK,                     }, 7000,       0 },
    {GCTX_FOLLOW_REPLY,                   {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_GAMB_BJ_LOSE,            GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GAMB_BJ_HIT,                    {GCTX_CAR_DRIVEBY_BURN_RUBBER, GCTX_UNK,                     GCTX_CAR_GET_IN,              GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GAMB_BJ_LOSE,                   {GCTX_CAR_DRIVEBY_TOO_FAST,    GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GAMB_BJ_STAY,                   {GCTX_CAR_FAST,                GCTX_UNK,                     GCTX_CAR_JUMP,                GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GAMB_BJ_WIN,                    {GCTX_CAR_FIRE,                GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GAMB_BJ_STICK,                  {GCTX_CAR_FAST,                GCTX_UNK,                     GCTX_CAR_JUMP,                GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GAMB_BJ_DOUBLE,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_FLIPPED,             GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GAMB_BJ_SPLIT,                  {GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_HIT_PED,             GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GAMB_CASINO_WIN,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_SLOW,                GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GAMB_CASINO_LOSE,               {GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_POLICE_PURSUIT,      GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GAMB_CONGRATS,                  {GCTX_CAR_FLIPPED,             GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GAMB_ROUL_CHAT,                 {GCTX_CAR_GET_IN,              GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 20000,      0 },
    {GCTX_GAMB_SLOT_WIN,                  {GCTX_CAR_HIT_PED,             GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GANG_FULL,                      {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_GAMB_BJ_STAY,            GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GANGBANG_NO,                    {GCTX_UNK,                     GCTX_UNK,                     GCTX_BOOZE_REQUEST,           GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GANGBANG_YES,                   {GCTX_UNK,                     GCTX_UNK,                     GCTX_BUM_BACK_OFF,            GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GENERIC_HI_MALE,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_CHAT,                    GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GENERIC_HI_FEMALE,              {GCTX_UNK,                     GCTX_UNK,                     GCTX_CHASED,                  GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GENERIC_INSULT_MALE,            {GCTX_UNK,                     GCTX_UNK,                     GCTX_COFFEE_DECLINE,          GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GENERIC_INSULT_FEMALE,          {GCTX_UNK,                     GCTX_UNK,                     GCTX_COFFEE_ACCEPT,           GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GIVING_HEAD,                    {GCTX_DRUG_AGGRESSIVE_LOW,     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GOOD_CITIZEN,                   {GCTX_UNK,                     GCTX_BUM_LATCH,               GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GUN_COOL,                       {GCTX_AFTER_SEX,               GCTX_BUMP,                    GCTX_UNK,                     GCTX_BOOZE_REQUEST,           GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GUN_RUN,                        {GCTX_CAR_JUMP,                GCTX_ATTACK_BY_PLAYER_LIKE,   GCTX_UNK,                     GCTX_COFFEE_ACCEPT,           GCTX_UNK,                     }, 7000,       0 },
    {GCTX_HAVING_SEX,                     {GCTX_DRUG_DEALER_DISLIKE,     GCTX_UNK,                     GCTX_DUCK,                    GCTX_UNK,                     GCTX_UNK,                     }, 2500,       0 },
    {GCTX_HAVING_SEX_MUFFLED,             {GCTX_UNK,                     GCTX_UNK,                     GCTX_EYEING_PED,              GCTX_UNK,                     GCTX_UNK,                     }, 2500,       0 },
    {GCTX_JACKED_GENERIC,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_ACCEPT_DATE_CALL,        GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_JACKED_CAR,                     {GCTX_APOLOGY,                 GCTX_UNK,                     GCTX_ABUSE_DA_NANG,           GCTX_BUM_BACK_OFF,            GCTX_COVER_ME,                }, 1000,       0 },
    {GCTX_JACKED_ON_STREET,               {GCTX_ARREST,                  GCTX_UNK,                     GCTX_UNK,                     GCTX_BUM_BACK_OFF_2,          GCTX_CRASH_BIKE,              }, 1000,       0 },
    {GCTX_JACKING_BIKE,                   {GCTX_ARREST_CRIM,             GCTX_ACCEPT_DATE_CALL,        GCTX_ACCEPT_DATE_REQUEST,     GCTX_BUMP,                    GCTX_GAMB_CASINO_WIN,         }, 1000,       0 },
    {GCTX_JACKING_CAR_FEM,                {GCTX_EYEING_PED,              GCTX_ACCEPT_DATE_CALL,        GCTX_BUM_BACK_OFF_2,          GCTX_BUM_LATCH,               GCTX_GAMB_CASINO_WIN,         }, 1000,       0 },
    {GCTX_JACKING_CAR_MALE,               {GCTX_EYEING_PED,              GCTX_ACCEPT_DATE_CALL,        GCTX_APOLOGY,                 GCTX_BUM_LATCH,               GCTX_GAMB_CASINO_WIN,         }, 1000,       0 },
    {GCTX_JACKING_GENERIC,                {GCTX_ARREST_CRIM,             GCTX_ACCEPT_DATE_CALL,        GCTX_ARREST,                  GCTX_BUMP,                    GCTX_GAMB_CASINO_WIN,         }, 1000,       0 },
    {GCTX_JOIN_GANG_NO,                   {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_GAMB_BJ_WIN,             GCTX_UNK,                     }, 1500,       0 },
    {GCTX_JOIN_GANG_YES,                  {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_GAMB_BJ_STICK,           GCTX_UNK,                     }, 1500,       0 },
    {GCTX_JOIN_ME_ASK,                    {GCTX_UNK,                     GCTX_UNK,                     GCTX_ARREST_CRIM,             GCTX_UNK,                     GCTX_UNK,                     }, 1000,       0 },
    {GCTX_JOIN_ME_REJECTED,               {GCTX_UNK,                     GCTX_UNK,                     GCTX_ARRESTED,                GCTX_UNK,                     GCTX_UNK,                     }, 3000,       0 },
    {GCTX_LIKE_CAR_REPLY,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_CLOTHES,       GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_LIKE_CLOTHES_REPLY,             {GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_HAIR,          GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_LIKE_DISMISS_FEMALE,            {GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_PHYS,          GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_LIKE_DISMISS_MALE,              {GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_SHOES,         GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_LIKE_DISMISS_REPLY,             {GCTX_ARRESTED,                GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUG_AGGRESSIVE_HIGH,    GCTX_UNK,                     }, 7000,       0 },
    {GCTX_LIKE_HAIR_REPLY,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_SMELL,         GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_LIKE_NEGATIVE_FEMALE,           {GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_TATTOO,        GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_LIKE_NEGATIVE_MALE,             {GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_WEATHER,       GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_LIKE_PHYS_REPLY,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_IGNORED,            GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_LIKE_SHOES_REPLY,               {GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_CAR,           GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_LIKE_SMELL_REPLY,               {GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_CLOTHES,       GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_LIKE_TATTOO_REPLY,              {GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_HAIR,          GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_MEET_GFRIEND_AGAIN_MAYBE,       {GCTX_UNK,                     GCTX_UNK,                     GCTX_EYEING_PED_THREAT,       GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_MEET_GFRIEND_AGAIN_NO,          {GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_PHYS,          GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_MEET_GFRIEND_AGAIN_YES,         {GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_SHOES,         GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_MOVE_IN,                        {GCTX_UNK,                     GCTX_ACCEPT_DATE_REQUEST,     GCTX_UNK,                     GCTX_CAR_CRASH,               GCTX_UNK,                     }, 7000,       0 },
    {GCTX_MUGGED,                         {GCTX_ATTACK_BY_PLAYER_LIKE,   GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_DRIVEBY_BURN_RUBBER, GCTX_UNK,                     }, 7000,       0 },
    {GCTX_MUGGING,                        {GCTX_FOLLOW_REPLY,            GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_DRIVEBY_TOO_FAST,    GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ORDER_ATTACK_MANY,              {GCTX_UNK,                     GCTX_UNK,                     GCTX_ATTACK_BY_PLAYER_LIKE,   GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ORDER_ATTACK_SINGLE,            {GCTX_UNK,                     GCTX_UNK,                     GCTX_ATTACK_GANG_BALLAS,      GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ORDER_DISBAND_MANY,             {GCTX_UNK,                     GCTX_UNK,                     GCTX_DANCE_IMPR_HIGH,         GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ORDER_DISBAND_ONE,              {GCTX_UNK,                     GCTX_UNK,                     GCTX_DANCE_IMPR_LOW,          GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ORDER_FOLLOW_FAR_MANY,          {GCTX_UNK,                     GCTX_UNK,                     GCTX_DANCE_IMPR_MED,          GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ORDER_FOLLOW_FAR_ONE,           {GCTX_UNK,                     GCTX_UNK,                     GCTX_DANCE_IMPR_NOT,          GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ORDER_FOLLOW_NEAR_MANY,         {GCTX_UNK,                     GCTX_UNK,                     GCTX_DODGE,                   GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ORDER_FOLLOW_NEAR_ONE,          {GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUG_AGGRESSIVE_HIGH,    GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ORDER_FOLLOW_VNEAR_MANY,        {GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUG_AGGRESSIVE_LOW,     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ORDER_FOLLOW_VNEAR_ONE,         {GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUG_DEALER_DISLIKE,     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ORDER_KEEP_UP_MANY,             {GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUG_DEALER_HATE,        GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ORDER_KEEP_UP_ONE,              {GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUG_REASONABLE_HIGH,    GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ORDER_WAIT_MANY,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUG_REASONABLE_LOW,     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ORDER_WAIT_ONE,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUGGED_CHAT,            GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_PCONV_AGREE_BAD,                {GCTX_CAR_POLICE_PURSUIT,      GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUG_AGGRESSIVE_LOW,     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_PCONV_AGREE_GOOD,               {GCTX_CAR_SLOW,                GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUG_DEALER_DISLIKE,     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_PCONV_ANS_NO,                   {GCTX_CAR_WAIT_FOR_ME,         GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUG_DEALER_HATE,        GCTX_UNK,                     }, 7000,       0 },
    {GCTX_PCONV_DISMISS,                  {GCTX_CAR_SINGALONG,           GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUG_REASONABLE_HIGH,    GCTX_UNK,                     }, 7000,       0 },
    {GCTX_PCONV_GREET_FEM,                {GCTX_CB_CHAT,                 GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUG_REASONABLE_LOW,     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_PCONV_GREET_MALE,               {GCTX_CHASE_FOOT,              GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUGGED_CHAT,            GCTX_UNK,                     }, 3000,       0 },
    {GCTX_PCONV_PART_FEM,                 {GCTX_CHASED,                  GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUGGED_IGNORE,          GCTX_UNK,                     }, 7000,       0 },
    {GCTX_PCONV_PART_MALE,                {GCTX_CHAT,                    GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_SMELL,         GCTX_UNK,                     }, 7000,       0 },
    {GCTX_PCONV_QUESTION,                 {GCTX_COFFEE_ACCEPT,           GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUGS_BUY,               GCTX_UNK,                     }, 7000,       0 },
    {GCTX_PCONV_STATE_BAD,                {GCTX_COFFEE_DECLINE,          GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUGS_SELL,              GCTX_UNK,                     }, 7000,       0 },
    {GCTX_PCONV_STATE_GOOD,               {GCTX_CONV_DISL_CAR,           GCTX_UNK,                     GCTX_UNK,                     GCTX_DUCK,                    GCTX_UNK,                     }, 7000,       0 },
    {GCTX_PICKUP_CASH,                    {GCTX_UNK,                     GCTX_UNK,                     GCTX_ATTACK_GANG_LSV,         GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_POLICE_BOAT,                    {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_GIVING_HEAD,             }, 10000,      0 },
    {GCTX_POLICE_HELICOPTER,              {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_GOOD_CITIZEN,            }, 10000,      0 },
    {GCTX_POLICE_OVERBOARD,               {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_GUN_COOL,                }, 10000,      0 },
    {GCTX_PULL_GUN,                       {GCTX_UNK,                     GCTX_UNK,                     GCTX_ATTACK_GANG_VLA,         GCTX_UNK,                     GCTX_UNK,                     }, 20000,      0 },
    {GCTX_ROPE,                           {GCTX_UNK,                     GCTX_CAR_FIRE,                GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_RUN_FROM_FIGHT,                 {GCTX_CONV_DISL_CLOTHES,       GCTX_UNK,                     GCTX_UNK,                     GCTX_EYEING_PED,              GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SAVED,                          {GCTX_ATTACK_GANG_LSV,         GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_FIRE,                GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SEARCH,                         {GCTX_UNK,                     GCTX_BAR_CHAT,                GCTX_UNK,                     GCTX_CAR_FLIPPED,             GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SHOCKED,                        {GCTX_ATTACK_GANG_VLA,         GCTX_APOLOGY,                 GCTX_UNK,                     GCTX_CAR_GET_IN,              GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SHOOT,                          {GCTX_UNK,                     GCTX_UNK,                     GCTX_ATTACK_PLAYER,           GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SHOOT_BALLAS,                   {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_TATTOO,        GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SHOOT_GENERIC,                  {GCTX_UNK,                     GCTX_ARREST,                  GCTX_UNK,                     GCTX_CAR_JUMP,                GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SHOOT_LSV,                      {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_COVER_ME,                GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SHOOT_VLA,                      {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_GAMB_BJ_DOUBLE,          GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SHOOT_FAMILIES,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_HIT_PED,             GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SHOP_BROWSE,                    {GCTX_CONV_DISL_HAIR,          GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SHOP_BUY,                       {GCTX_CONV_DISL_PHYS,          GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SHOP_SELL,                      {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUGS_SELL,              }, 7000,       0 },
    {GCTX_SHOP_LEAVE,                     {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_FOLLOW_ARRIVE,           }, 7000,       0 },
    {GCTX_SOLICIT,                        {GCTX_DRUG_DEALER_HATE,        GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SOLICIT_GEN_NO,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_WEATHER,       GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SOLICIT_GEN_YES,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_COVER_ME,                GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SOLICIT_PRO_NO,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_BUM_LATCH,               GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SOLICIT_PRO_YES,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_BOOZE_RECEIVE,           GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SOLICIT_THANKS,                 {GCTX_DRUG_REASONABLE_HIGH,    GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SOLICIT_UNREASONABLE,           {GCTX_DRUG_REASONABLE_LOW,     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SOLO,                           {GCTX_UNK,                     GCTX_CAR_CRASH,               GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SPLIFF_RECEIVE,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_POLICE_PURSUIT,      GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SPLIFF_REQUEST,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_SLOW,                GCTX_UNK,                     }, 7000,       0 },
    {GCTX_STEALTH_ALERT_SOUND,            {GCTX_ABUSE_GANG_LSV,          GCTX_ABUSE_GANG_LSV,          GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_STEALTH_ALERT_SIGHT,            {GCTX_ABUSE_GANG_BALLAS,       GCTX_ABUSE_GANG_BALLAS,       GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_STEALTH_ALERT_GENERIC,          {GCTX_NO_SPEECH,               GCTX_NO_SPEECH,               GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_STEALTH_DEF_SIGHTING,           {GCTX_ABUSE_DA_NANG,           GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_STEALTH_NOTHING_THERE,          {GCTX_UNK,                     GCTX_AFTER_SEX,               GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SURROUNDED,                     {GCTX_UNK,                     GCTX_ATTACK_GANG_VLA,         GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_TARGET,                         {GCTX_UNK,                     GCTX_ATTACK_PLAYER,           GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_TAKE_TURF_LAS_COLINAS,          {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 3000,       0 },
    {GCTX_TAKE_TURF_LOS_FLORES,           {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 3000,       0 },
    {GCTX_TAKE_TURF_EAST_BEACH,           {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 3000,       0 },
    {GCTX_TAKE_TURF_EAST_LS,              {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 3000,       0 },
    {GCTX_TAKE_TURF_JEFFERSON,            {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 3000,       0 },
    {GCTX_TAKE_TURF_GLEN_PARK,            {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 3000,       0 },
    {GCTX_TAKE_TURF_IDLEWOOD,             {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 3000,       0 },
    {GCTX_TAKE_TURF_GANTON,               {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 3000,       0 },
    {GCTX_TAKE_TURF_LITTLE_MEXICO,        {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 3000,       0 },
    {GCTX_TAKE_TURF_WILLOWFIELD,          {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 3000,       0 },
    {GCTX_TAKE_TURF_PLAYA_DEL_SEVILLE,    {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 3000,       0 },
    {GCTX_TAKE_TURF_TEMPLE,               {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 3000,       0 },
    {GCTX_TAXI_BAIL,                      {GCTX_CONV_DISL_SHOES,         GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_TAXI_HAIL,                      {GCTX_CONV_DISL_SMELL,         GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_WAIT_FOR_ME,         GCTX_UNK,                     }, 7000,       0 },
    {GCTX_TAXI_HIT_PED,                   {GCTX_CONV_DISL_TATTOO,        GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_TAXI_START,                     {GCTX_CONV_DISL_WEATHER,       GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_TAXI_SUCCESS,                   {GCTX_CONV_IGNORED,            GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_TAXI_TIP,                       {GCTX_CONV_LIKE_CAR,           GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_TRAPPED,                        {GCTX_ATTACK_PLAYER,           GCTX_UNK,                     GCTX_UNK,                     GCTX_CB_CHAT,                 GCTX_UNK,                     }, 3500,       0 },
    {GCTX_VALET_BAD,                      {GCTX_CRASH_CAR,               GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_VALET_GOOD,                     {GCTX_CRASH_GENERIC,           GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_VALET_PARK_CAR,                 {GCTX_CRIMINAL_PLEAD,          GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_VAN,                            {GCTX_UNK,                     GCTX_ATTACK_GANG_BALLAS,      GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_VICTIM,                         {GCTX_UNK,                     GCTX_ATTACK_GANG_LSV,         GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_WEATHER_DISL_REPLY,             {GCTX_UNK,                     GCTX_UNK,                     GCTX_CRASH_CAR,               GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_WEATHER_LIKE_REPLY,             {GCTX_UNK,                     GCTX_UNK,                     GCTX_CRASH_GENERIC,           GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_WHERE_YOU_FROM_NEG,             {GCTX_UNK,                     GCTX_UNK,                     GCTX_GENERIC_HI_MALE,         GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_WHERE_YOU_FROM_POS,             {GCTX_UNK,                     GCTX_UNK,                     GCTX_BUMP,                    GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SPANKED,                        {GCTX_UNK,                     GCTX_UNK,                     GCTX_FOLLOW_CONSTANT,         GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SPANKING,                       {GCTX_UNK,                     GCTX_UNK,                     GCTX_FOLLOW_REPLY,            GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_SPANKING_MUFFLED,               {GCTX_UNK,                     GCTX_UNK,                     GCTX_GAMB_BJ_HIT,             GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GREETING_GFRIEND,               {GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_CAR,           GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_PARTING_GFRIEND,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_TATTOO,        GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_UH_HUH,                         {GCTX_UNK,                     GCTX_UNK,                     GCTX_CRASH_BIKE,              GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CLEAR_ATTACHED_PEDS,            {GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_WAIT_FOR_ME,         GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_AGREE_TO_DO_DRIVEBY,            {GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_FAST,                GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_AGREE_TO_LET_DRIVE,             {GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_FIRE,                GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_MICHELLE_TAKE_CAR,              {GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_SMELL,         GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ACCEPT_SEX,                     {GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_DRIVEBY_TOO_FAST,    GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_DECLINE_SEX,                    {GCTX_UNK,                     GCTX_UNK,                     GCTX_CHASE_FOOT,              GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GIVE_NUMBER_YES,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUGS_SELL,              GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GIVE_NUMBER_NO,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUGS_BUY,               GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_WHERE_YOU_FROM,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CHASE_FOOT,              GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GANGBANG,                       {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_BOOZE_RECEIVE,           GCTX_UNK,                     }, 7000,       0 },
    {GCTX_WHERE_YOU_FROM_POS_REPLY,       {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CHASED,                  GCTX_UNK,                     }, 7000,       0 },
    {GCTX_DRIVE_THROUGH_TAUNT,            {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_ATTACK_GANG_BALLAS,      GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ATTACK_CAR,                     {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_ABUSE_GANG_BALLAS,       GCTX_UNK,                     }, 7000,       0 },
    {GCTX_TIP_CAR,                        {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_SINGALONG,           GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CHASE_CAR,                      {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_ABUSE_RIFA,              GCTX_UNK,                     }, 7000,       0 },
    {GCTX_ENEMY_GANG_WASTED,              {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_ATTACK_GANG_VLA,         GCTX_UNK,                     }, 7000,       0 },
    {GCTX_PLAYER_WASTED,                  {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_FAST,                GCTX_UNK,                     }, 7000,       0 },
    {GCTX_CHASE,                          {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GFRIEND_REQ_DATE_DESPERATE,     {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_HAIR,          }, 7000,       0 },
    {GCTX_GFRIEND_REQ_DATE_NORMAL,        {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_PHYS,          }, 7000,       0 },
    {GCTX_GFRIEND_REQ_MEAL_DESPERATE,     {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_TATTOO,        }, 7000,       0 },
    {GCTX_GFRIEND_REQ_MEAL_NORMAL,        {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_WEATHER,       }, 7000,       0 },
    {GCTX_GFRIEND_REQ_DRIVE_DESPERATE,    {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_SHOES,         }, 7000,       0 },
    {GCTX_GFRIEND_REQ_DRIVE_NORMAL,       {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_SMELL,         }, 7000,       0 },
    {GCTX_GFRIEND_REQ_DANCE_DESPERATE,    {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_CAR,           }, 7000,       0 },
    {GCTX_GFRIEND_REQ_DANCE_NORMAL,       {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_DISL_CLOTHES,       }, 7000,       0 },
    {GCTX_GFRIEND_REQ_SEX_DESPERATE,      {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_IGNORED,            }, 7000,       0 },
    {GCTX_GFRIEND_REQ_SEX_NORMAL,         {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_CAR,           }, 7000,       0 },
    {GCTX_GFRIEND_BORED_1,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_APOLOGY,                 }, 7000,       0 },
    {GCTX_GFRIEND_BORED_2,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_ARREST,                  }, 7000,       0 },
    {GCTX_GFRIEND_STORY,                  {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_SHOES,         }, 7000,       0 },
    {GCTX_GFRIEND_LIKE_MEAL_DEST,         {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_POLICE_PURSUIT,      }, 7000,       0 },
    {GCTX_GFRIEND_LIKE_CLUB_DEST,         {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_HIT_PED,             }, 7000,       0 },
    {GCTX_GFRIEND_OFFER_DANCE,            {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CHASE_FOOT,              }, 7000,       0 },
    {GCTX_GFRIEND_ENJOYED_MEAL_HIGH,      {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_BOOZE_REQUEST,           }, 7000,       0 },
    {GCTX_GFRIEND_ENJOYED_EVENT_LOW,      {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_BOOZE_RECEIVE,           }, 7000,       0 },
    {GCTX_GFRIEND_ENJOYED_CLUB_HIGH,      {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_BLOCKED,                 }, 7000,       0 },
    {GCTX_GFRIEND_TAKE_HOME_HAPPY,        {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_TATTOO,        }, 7000,       0 },
    {GCTX_GFRIEND_TAKE_HOME_ANGRY,        {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_SMELL,         }, 7000,       0 },
    {GCTX_GFRIEND_COFFEE,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_ATTACK_GANG_VLA,         }, 7000,       0 },
    {GCTX_GFRIEND_MOAN,                   {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_WAIT_FOR_ME,         }, 7000,       0 },
    {GCTX_GFRIEND_MOAN_MUFFLED,           {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_SINGALONG,           }, 7000,       0 },
    {GCTX_GFRIEND_HEAD,                   {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_CRASH,               }, 7000,       0 },
    {GCTX_GFRIEND_CLIMAX_HIGH,            {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_ATTACK_BY_PLAYER_LIKE,   }, 7000,       0 },
    {GCTX_GFRIEND_CLIMAX_HIGH_MUFFLED,    {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_ATTACK_GANG_BALLAS,      }, 7000,       0 },
    {GCTX_GFRIEND_CLIMAX_LOW,             {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_ATTACK_GANG_LSV,         }, 7000,       0 },
    {GCTX_GFRIEND_SEX_GOOD,               {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_HAIR,          }, 7000,       0 },
    {GCTX_GFRIEND_SEX_GOOD_MUFFLED,       {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_PHYS,          }, 7000,       0 },
    {GCTX_GFRIEND_SEX_BAD,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CONV_LIKE_CLOTHES,       }, 7000,       0 },
    {GCTX_GFRIEND_MEET_AGAIN,             {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_SLOW,                }, 7000,       0 },
    {GCTX_GFRIEND_JEALOUS,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_FIRE,                }, 7000,       0 },
    {GCTX_GFRIEND_JEALOUS_REPLY,          {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_FLIPPED,             }, 7000,       0 },
    {GCTX_GFRIEND_GOODBYE_HAPPY,          {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_BUMP,                    }, 7000,       0 },
    {GCTX_GFRIEND_GOODBYE_ANGRY,          {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_BUM_LATCH,               }, 7000,       0 },
    {GCTX_GFRIEND_LEFT_BEHIND,            {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_GET_IN,              }, 7000,       0 },
    {GCTX_GFRIEND_HELLO,                  {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_DRIVEBY_BURN_RUBBER, }, 7000,       0 },
    {GCTX_GFRIEND_GOODBYE,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_BUM_BACK_OFF_2,          }, 7000,       0 },
    {GCTX_GFRIEND_PICKUP_LOCATION,        {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GFRIEND_PARK_UP,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CHAT,                    }, 7000,       0 },
    {GCTX_GFRIEND_PARK_LOCATION_HATE,     {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CHASED,                  }, 7000,       0 },
    {GCTX_GFRIEND_GIFT_LIKE,              {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_BUM_BACK_OFF,            }, 7000,       0 },
    {GCTX_GFRIEND_CHANGE_RADIO_FAVE,      {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_ARRESTED,                }, 7000,       0 },
    {GCTX_GFRIEND_CHANGE_RADIO_BACK,      {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_ARREST_CRIM,             }, 7000,       0 },
    {GCTX_GFRIEND_DO_A_DRIVEBY,           {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_GAMB_CASINO_LOSE,        }, 7000,       0 },
    {GCTX_GFRIEND_START_A_FIGHT,          {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_GAMB_CONGRATS,           }, 7000,       0 },
    {GCTX_GFRIEND_REJECT_DATE,            {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_COFFEE_DECLINE,          }, 7000,       0 },
    {GCTX_GFRIEND_REQUEST_TO_DRIVE_CAR,   {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_GENERIC_HI_FEMALE,       }, 7000,       0 },
    {GCTX_GFRIEND_DROP_PLAYER_DRIVE_AWAY, {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_GENERIC_HI_MALE,         }, 7000,       0 },
    {GCTX_GFRIEND_DISLIKE_CURRENT_ZONE,   {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_ATTACK_PLAYER,           }, 7000,       0 },
    {GCTX_GFRIEND_LIKE_CURRENT_ZONE,      {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_JUMP,                }, 7000,       0 },
    {GCTX_GFRIEND_HIT_BY_PLAYER_WARNING,  {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_DRIVEBY_TOO_FAST,    }, 7000,       0 },
    {GCTX_GFRIEND_DUMP_PLAYER_LIVE,       {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_BAR_CHAT,                }, 7000,       0 },
    {GCTX_GFRIEND_DUMP_PLAYER_PHONE,      {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_GFRIEND_SEX_APPEAL_TOO_LOW,     {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUGGED_CHAT,            }, 7000,       0 },
    {GCTX_GFRIEND_PHYSIQUE_CRITIQUE,      {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUG_REASONABLE_HIGH,    }, 7000,       0 },
    {GCTX_GFRIEND_INTRO,                  {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CAR_FAST,                }, 7000,       0 },
    {GCTX_GFRIEND_NEG_RESPONSE,           {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_CB_CHAT,                 }, 7000,       0 },
    {GCTX_GFRIEND_POS_RESPONSE,           {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_COFFEE_ACCEPT,           }, 7000,       0 },
    {GCTX_BOXING_CHEER,                   {GCTX_FOLLOW_ARRIVE,           GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 3000,       0 },
    {GCTX_BOUGHT_ENOUGH,                  {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_GUN_RUN,                 }, 2000,       0 },
    {GCTX_GIVE_PRODUCT,                   {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUGS_SELL,              }, 2000,       0 },
    {GCTX_NO_MONEY,                       {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_DUCK,                    }, 2000,       0 },
    {GCTX_PLAYER_SICK,                    {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_HAVING_SEX,              }, 7000,       0 },
    {GCTX_REMOVE_TATTOO,                  {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_FOLLOW_REPLY,            }, 3000,       0 },
    {GCTX_SHOP_CLOSED,                    {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_HAVING_SEX_MUFFLED,      }, 7000,       0 },
    {GCTX_SHOW_CHANGINGROOM,              {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_JACKED_CAR,              }, 3000,       0 },
    {GCTX_SHOP_CHAT,                      {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_EYEING_PED_THREAT,       }, 15000,      0 },
    {GCTX_TAKE_A_SEAT,                    {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_FIGHT,                   }, 7000,       0 },
    {GCTX_THANKS_FOR_CUSTOM,              {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_FOLLOW_ARRIVE,           }, 7000,       0 },
    {GCTX_WELCOME_TO_SHOP,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_JACKED_GENERIC,          }, 7000,       0 },
    {GCTX_WHAT_WANT,                      {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_FOLLOW_CONSTANT,         }, 2000,       0 },
    {GCTX_PHOTO_CARL,                     {GCTX_UNK,                     GCTX_UNK,                     GCTX_EYEING_PLAYER,           GCTX_UNK,                     GCTX_UNK,                     }, 4000,       0 },
    {GCTX_PHOTO_CHEESE,                   {GCTX_UNK,                     GCTX_UNK,                     GCTX_FIGHT,                   GCTX_UNK,                     GCTX_UNK,                     }, 4000,       0 },
    {GCTX_SINGING,                        {GCTX_UNK,                     GCTX_UNK,                     GCTX_FOLLOW_ARRIVE,           GCTX_UNK,                     GCTX_UNK,                     }, 30000,      0 },
    {GCTX_STOMACH_RUMBLE,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_GAMB_BJ_STAY,            GCTX_UNK,                     GCTX_UNK,                     }, 5000,       0 },
    {GCTX_BREATHING,                      {GCTX_UNK,                     GCTX_UNK,                     GCTX_DRUGGED_IGNORE,          GCTX_UNK,                     GCTX_UNK,                     }, 4000,       0 },
    {GCTX_PAIN_COUGH,                     {GCTX_ARRESTED,                GCTX_ARRESTED,                GCTX_ABUSE_GANG_BALLAS,       GCTX_ARRESTED,                GCTX_ARRESTED,                }, 3000,       0 },
    {GCTX_PAIN_DEATH_DROWN,               {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_PAIN_DEATH_HIGH,                {GCTX_ATTACK_BY_PLAYER_LIKE,   GCTX_ATTACK_BY_PLAYER_LIKE,   GCTX_ABUSE_GANG_LSV,          GCTX_ATTACK_BY_PLAYER_LIKE,   GCTX_ATTACK_BY_PLAYER_LIKE,   }, 2000,       0 },
    {GCTX_PAIN_DEATH_LOW,                 {GCTX_ATTACK_GANG_BALLAS,      GCTX_ATTACK_GANG_BALLAS,      GCTX_ABUSE_GANG_LSV,          GCTX_ATTACK_GANG_BALLAS,      GCTX_ATTACK_GANG_BALLAS,      }, 2000,       0 },
    {GCTX_PAIN_HIGH,                      {GCTX_ATTACK_GANG_LSV,         GCTX_ATTACK_GANG_LSV,         GCTX_ABUSE_RIFA,              GCTX_ATTACK_GANG_LSV,         GCTX_ATTACK_GANG_LSV,         }, 2000,       0 },
    {GCTX_PAIN_LOW,                       {GCTX_ATTACK_GANG_LSV,         GCTX_ATTACK_GANG_LSV,         GCTX_ABUSE_DA_NANG,           GCTX_ATTACK_GANG_LSV,         GCTX_ATTACK_GANG_LSV,         }, 2000,       0 },
    {GCTX_PAIN_ON_FIRE,                   {GCTX_ATTACK_GANG_VLA,         GCTX_ATTACK_GANG_VLA,         GCTX_ABUSE_MAFIA,             GCTX_ATTACK_GANG_VLA,         GCTX_ATTACK_GANG_VLA,         }, 100 ,       0 },
    {GCTX_PAIN_PANIC,                     {GCTX_ATTACK_PLAYER,           GCTX_ATTACK_PLAYER,           GCTX_UNK,                     GCTX_ATTACK_PLAYER,           GCTX_ATTACK_PLAYER,           }, 8000,       0 },
    {GCTX_PAIN_SPRAYED,                   {GCTX_BAR_CHAT,                GCTX_BAR_CHAT,                GCTX_UNK,                     GCTX_BAR_CHAT,                GCTX_BAR_CHAT,                }, 2000,       0 },
    {GCTX_PAIN_CJ_BOXING,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_NO_SPEECH,               GCTX_UNK,                     GCTX_UNK,                     }, 3000,       0 },
    {GCTX_PAIN_CJ_GRUNT,                  {GCTX_UNK,                     GCTX_UNK,                     GCTX_ABUSE_GANG_FAMILIES,     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_PAIN_CJ_PUKE,                   {GCTX_UNK,                     GCTX_UNK,                     GCTX_AFTER_SEX,               GCTX_UNK,                     GCTX_UNK,                     }, 3000,       0 },
    {GCTX_PAIN_CJ_PANT_IN,                {GCTX_UNK,                     GCTX_UNK,                     GCTX_ACCEPT_DATE_CALL,        GCTX_UNK,                     GCTX_UNK,                     }, 1000,       0 },
    {GCTX_PAIN_CJ_PANT_OUT,               {GCTX_UNK,                     GCTX_UNK,                     GCTX_ACCEPT_DATE_REQUEST,     GCTX_UNK,                     GCTX_UNK,                     }, 1000,       0 },
    {GCTX_PAIN_CJ_STRAIN,                 {GCTX_UNK,                     GCTX_UNK,                     GCTX_APOLOGY,                 GCTX_UNK,                     GCTX_UNK,                     }, 3000,       0 },
    {GCTX_PAIN_CJ_STRAIN_EXHALE,          {GCTX_UNK,                     GCTX_UNK,                     GCTX_ARREST,                  GCTX_UNK,                     GCTX_UNK,                     }, 3000,       0 },
    {GCTX_PAIN_CJ_SWIM_GASP,              {GCTX_UNK,                     GCTX_UNK,                     GCTX_ARREST_CRIM,             GCTX_UNK,                     GCTX_UNK,                     }, 10000,      0 },
    {GCTX_PAIN_CJ_DROWNING,               {GCTX_UNK,                     GCTX_UNK,                     GCTX_ABUSE_GANG_VLA,          GCTX_UNK,                     GCTX_UNK,                     }, 2000,       0 },
    {GCTX_PAIN_CJ_HIGH_FALL,              {GCTX_UNK,                     GCTX_UNK,                     GCTX_ABUSE_TRIAD,             GCTX_UNK,                     GCTX_UNK,                     }, 3000,       0 },
    {GCTX_END,                            {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 7000,       0 },
    {GCTX_UNK,                            {GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     GCTX_UNK,                     }, 65535,      0 },
}};

void CAEPedSpeechAudioEntity::InjectHooks() {
    RH_ScopedVirtualClass(CAEPedSpeechAudioEntity, 0x85F310, 8);
    RH_ScopedCategory("Audio/Entities");

    RH_ScopedInstall(Constructor, 0x4E4F10);
    RH_ScopedInstall(IsGlobalContextImportantForInterupting, 0x4E4600);
    RH_ScopedInstall(IsGlobalContextUberImportant, 0x4E46F0);
    RH_ScopedInstall(GetNextMoodToUse, 0x4E4700);
    RH_ScopedInstall(GetVoiceForMood, 0x4E4760);
    RH_ScopedInstall(CanWePlayScriptedSpeech, 0x4E4950);
    RH_ScopedInstall(GetSpeechContextVolumeOffset, 0x4E4AE0);
    RH_ScopedInstall(RequestPedConversation, 0x4E50E0);
    RH_ScopedInstall(ReleasePedConversation, 0x4E52A0);
    RH_ScopedInstall(GetCurrentCJMood, 0x4E53B0);
    RH_ScopedInstall(StaticInitialise, 0x5B98C0);
    RH_ScopedInstall(GetSpecificSpeechContext, 0x4E4470);
    RH_ScopedInstall(Service, 0x4E3710);
    RH_ScopedInstall(Reset, 0x4E37B0);
    RH_ScopedInstall(ReservePedConversationSpeechSlots, 0x4E37F0);
    RH_ScopedInstall(ReservePlayerConversationSpeechSlot, 0x4E3870);
    RH_ScopedInstall(RequestPlayerConversation, 0x4E38C0);
    RH_ScopedInstall(ReleasePlayerConversation, 0x4E3960);
    RH_ScopedInstall(SetUpConversation, 0x4E3A00);
    RH_ScopedInstall(GetAudioPedType, 0x4E3C60);
    RH_ScopedInstall(GetVoice, 0x4E3CD0);
    RH_ScopedInstall(DisableAllPedSpeech, 0x4E3EB0);
    RH_ScopedInstall(IsGlobalContextPain, 0x4E44F0);
    RH_ScopedInstall(SetCJMood, 0x4E3ED0);
    RH_ScopedInstall(EnableAllPedSpeech, 0x4E3EC0);
    RH_ScopedInstall(IsCJDressedInForGangSpeech, 0x4E4270);
    RH_ScopedInstall(GetSexForSpecialPed, 0x4E4260);
    RH_ScopedInstall(IsGlobalContextImportantForWidescreen, 0x4E46B0);
    RH_ScopedInstall(GetRepeatTime, 0x4E47E0, { .reversed = false });
    RH_ScopedInstall(LoadAndPlaySpeech, 0x4E4840);
    RH_ScopedInstall(GetNumSlotsPlayingContext, 0x4E49B0);
    RH_ScopedInstall(GetNextPlayTime, 0x4E49E0);
    RH_ScopedInstall(SetNextPlayTime, 0x4E4A20);
    RH_ScopedInstall(DisablePedSpeech, 0x4E56D0);
    RH_ScopedInstall(DisablePedSpeechForScriptSpeech, 0x4E5700);
    RH_ScopedInstall(CanPedSayGlobalContext, 0x4E5730, { .reversed = false });
    RH_ScopedInstall(GetVoiceAndTypeFromModel, 0x4E58C0);
    RH_ScopedInstall(GetSoundAndBankIDs, 0x4E5920, { .reversed = false });
    RH_ScopedInstall(CanWePlayGlobalSpeechContext, 0x4E5F10, { .reversed = false });
    RH_ScopedInstall(AddSayEvent, 0x4E6550, { .reversed = false });
    RH_ScopedInstall(Initialise, 0x4E68D0, { .reversed = false });
    RH_ScopedInstall(CanPedHoldConversation, 0x4E69E0, { .reversed = false });
    RH_ScopedInstall(IsGlobalContextImportantForStreaming, 0x4E4510, { .reversed = false });
    RH_ScopedInstall(EnablePedSpeech, 0x4E3F70);
    RH_ScopedInstall(EnablePedSpeechForScriptSpeech, 0x4E3F90);
    RH_ScopedInstall(StopCurrentSpeech, 0x4E3FB0, { .reversed = false });
    RH_ScopedInstall(GetSoundAndBankIDsForScriptedSpeech, 0x4E4400, { .reversed = false });
    RH_ScopedInstall(GetSexFromModel, 0x4E4200, { .reversed = false });
    RH_ScopedInstall(GetPedTalking, 0x4E3F50);
    RH_ScopedInstall(GetVoiceAndTypeForSpecialPed, 0x4E4170, { .reversed = false });
    RH_ScopedVMTInstall(UpdateParameters, 0x4E3520, { .reversed = false });
    RH_ScopedVMTInstall(AddScriptSayEvent, 0x4E4F70, { .reversed = false });
    RH_ScopedVMTInstall(Terminate, 0x4E5670, { .reversed = false });
    RH_ScopedVMTInstall(PlayLoadedSound, 0x4E5CD0, { .reversed = false });
    RH_ScopedVMTInstall(GetAllocatedVoice, 0x4E4120);
    RH_ScopedVMTInstall(WillPedChatAboutTopic, 0x4E5800);
    RH_ScopedVMTInstall(GetPedType, 0x4E4130);
    RH_ScopedVMTInstall(IsPedFemaleForAudio, 0x4E4150);
}

// 0x4E4600
bool __stdcall CAEPedSpeechAudioEntity::IsGlobalContextImportantForInterupting(int16 globalCtx) {
    switch (globalCtx) {
    case 13:
    case 15:
    case 125:
    case 126:
    case 127:
        return true;
    default:
        return false;
    }
}

// 0x4E46F0 - unused
bool CAEPedSpeechAudioEntity::IsGlobalContextUberImportant(int16 globalCtx) {
    return false;
}

// 0x4E4700
int16 __stdcall CAEPedSpeechAudioEntity::GetNextMoodToUse(eCJMood lastMood) {
    switch (lastMood) {
    case MOOD_AG:
    case MOOD_PR: return MOOD_AR;
    case MOOD_PG: return MOOD_AG;
    case MOOD_WG: return MOOD_CG;
    default:      return MOOD_CR;
    }
}

// 0x4E4760
int32 __stdcall CAEPedSpeechAudioEntity::GetVoiceForMood(int16 mood) {
    auto rnd = CAEAudioUtility::GetRandomNumberInRange(0, 1);
    if (mood < 0 || mood >= 10)
        return rnd + 10;
    return rnd + 2 * mood;
}

// 0x4E4950
int16 CAEPedSpeechAudioEntity::CanWePlayScriptedSpeech() {
    for (auto i = 0; i < PED_TYPE_SPC; i++) {
        const auto slot = (s_NextSpeechSlot + i) % PED_TYPE_SPC;
        if (s_PedSpeechSlots[slot].Status == CAEPedSpeechSlot::eStatus::FREE) {
            s_NextSpeechSlot = slot;
            return slot;
        }
    }
    return -1;
}

// 0x4E4AE0
float CAEPedSpeechAudioEntity::GetSpeechContextVolumeOffset(eGlobalSpeechContextS16 gctx) {
    const auto CalculateStrainVolumeOffset = [](float base) {
        const auto t = std::clamp(CStats::GetStatValue(STAT_FAT) - CStats::GetStatValue(STAT_MUSCLE), -1.f, 1.f);
        return (t + 1.f) * 0.5f * base + base;
    };
    switch (gctx) {
    case GCTX_STOMACH_RUMBLE:        return -6.f; // 0x4E4CBB
    case GCTX_BREATHING:             return -12.f; // 0x4E4CC7
    case GCTX_PAIN_CJ_STRAIN:        return CalculateStrainVolumeOffset(-18.f); // 0x4E4B08
    case GCTX_PAIN_CJ_STRAIN_EXHALE: return CalculateStrainVolumeOffset(-21.f); // 0x4E4BE2
    case GCTX_PAIN_CJ_DROWNING:      return 3.f; // 0x4E4CBE
    default:                         return 0.f; // 0x4E4CD0
    }
}

// 0x4E50E0
bool CAEPedSpeechAudioEntity::RequestPedConversation(CPed* pedA, CPed* pedB) {
    if (s_bAllSpeechDisabled || s_bPedConversationHappening || s_bPlayerConversationHappening) {
        return false;
    }
    if (pedA->m_pedSpeech.GetAllocatedVoice() == pedB->m_pedSpeech.GetAllocatedVoice()) {
        return false;
    }
    const auto CheckCanPedTalk = [](CPed* p) {
        return !p->m_pedSpeech.IsAllSpeechDisabled()
            && p->CanPedHoldConversation()
            && !p->GetPedTalking()
            && CVector::DistSqr(TheCamera.GetPosition(), p->GetPosition()) <= sq(40.f);
    };
    if (!CheckCanPedTalk(pedA) || !CheckCanPedTalk(pedB)) {
        return false;
    }
    if (!ReservePedConversationSpeechSlots()) {
        return false;
    }
    s_bPedConversationHappening = true;
    s_pConversationPed1         = pedA;
    s_pConversationPed2         = pedB;
    SetUpConversation();
    return true;
}

// 0x4E52A0
void CAEPedSpeechAudioEntity::ReleasePedConversation() {
    if (!s_bPedConversationHappening) {
        return;
    }
    if (s_pConversationPedSlot1 == -1 || s_pConversationPedSlot2 == -1) {
        return;
    }

    const auto ReleaseConversationFromSlot = [](CPed*& convoPed, auto& slotID) {
        auto& ss = s_PedSpeechSlots[slotID];
        switch (ss.Status) {
        case CAEPedSpeechSlot::eStatus::FREE:
        case CAEPedSpeechSlot::eStatus::RESERVED:
            break;
        default:
            ss.AudioEntity->StopCurrentSpeech();
        }
        ss       = {}; // Reset slot
        slotID   = -1;
        convoPed = nullptr;
    };
    ReleaseConversationFromSlot(s_pConversationPed1, s_pConversationPedSlot1);
    ReleaseConversationFromSlot(s_pConversationPed2, s_pConversationPedSlot2);

    s_bPedConversationHappening = false;
}

// 0x4E53B0
int16 CAEPedSpeechAudioEntity::GetCurrentCJMood() {
    const auto* const plyr = FindPlayerPed();
    if (!plyr) {
        return MOOD_CR;
    }

    const auto isMoodOverrideActive = s_nCJMoodOverrideTime >= CTimer::GetTimeInMS();
    
    const auto CheckCJIsWellDressed = [&] { // 0x4E53DF
        if (isMoodOverrideActive && s_nCJWellDressed != -1) {
            return s_nCJWellDressed != 0;
        }
        return CStats::GetStatValue(STAT_CLOTHES_RESPECT) >= 650.f
            && CStats::GetStatValue(STAT_FASHION_BUDGET) >= 10'000.f;
    };

    const auto CheckCJIsGangBanging = [&] { // 0x4E5440
        if (isMoodOverrideActive && s_nCJGangBanging != -1) {
            return s_nCJGangBanging != 0;
        }
        if (IsCJDressedInForGangSpeech()) {
            return true;
        }
        auto& plyrGrp = plyr->GetPlayerGroup();
        if (plyrGrp.GetMembership().CountMembersExcludingLeader() <= 1) {
            return true;
        }
        const auto& mem = plyrGrp.GetMembership().GetMembers().front(); // The one-and-only member (This isnt the same as `GetMember(0)`!!!)
        if (mem.m_nPedType == PED_TYPE_GANG2) {
            return true;
        }
        auto& memSpeech = mem.m_pedSpeech;
        return memSpeech.m_PedAudioType == PED_TYPE_GANG
            && notsa::contains({ VOICE_GNG_RYDER, VOICE_GNG_SWEET, VOICE_GNG_SMOKE }, (eGngSpeechVoices)memSpeech.m_VoiceID);
    };

    const auto CheckCJIsFat = [&] { // 0x4E54E0
        if (isMoodOverrideActive && s_nCJFat != -1) {
            return s_nCJFat != 0;
        }
        return CStats::GetStatValue(STAT_FAT) >= 600.f
            && CStats::GetStatValue(STAT_FAT) - 200.f > CStats::GetStatValue(STAT_MUSCLE);
    };

    const auto DeriveMood = [&](eCJMood basicMood) { // 0x4E55CC
        if (isMoodOverrideActive && s_nCJBasicMood != MOOD_UNK) { // 0x4E5592
            basicMood = s_nCJBasicMood;
        }
        switch (basicMood) {
        case MOOD_AR:
            return CheckCJIsFat()
                ? MOOD_AR
                : MOOD_AG;
        case MOOD_CR: {
            if (CheckCJIsGangBanging()) {
                return MOOD_CG;
            }
            if (CheckCJIsFat()) {
                return MOOD_CF;
            }
            return CheckCJIsWellDressed()
                ? MOOD_CD
                : MOOD_CR;
        }
        case MOOD_PR:
            return CheckCJIsGangBanging()
                ? MOOD_PG
                : MOOD_PR;
        case MOOD_WR:
            return CheckCJIsGangBanging()
                ? MOOD_WG
                : MOOD_WR;
        default:
            return MOOD_CR;
        }
    };

    if (FindPlayerWanted()->GetWantedLevel() > 3) { // 0x4E5537
        return DeriveMood(MOOD_PR);
    }

    if (FindPlayerWanted()->GetWantedLevel() > 1) { // 0x4E554B
        return DeriveMood(MOOD_AR);
    }

    if (CTheScripts::LastMissionPassedTime == -1) { // 0x4E555C
        if (CTimer::GetTimeInMS() >= CTheScripts::LastMissionPassedTime) {
            return CTimer::GetTimeInMS() < CTheScripts::LastMissionPassedTime + 180'000
                ? DeriveMood(MOOD_WR)
                : DeriveMood(MOOD_CR);
        } else {
            CTheScripts::LastMissionPassedTime = CTimer::GetTimeInMS();
        }
    }

    return DeriveMood(MOOD_CR); // 0x4E5579
}

// 0x5B98C0
void CAEPedSpeechAudioEntity::StaticInitialise() {
    rng::fill(s_PedSpeechSlots, CAEPedSpeechSlot{});
    rng::fill(s_PhraseMemory, tPhraseMemory{});

    Reset();

    s_pConversationPed1            = nullptr;
    s_pConversationPed2            = nullptr;
    s_pConversationPedSlot1        = 0;
    s_pConversationPedSlot2        = 0;
    s_pPlayerConversationPed       = nullptr;
    s_bPedConversationHappening    = false;
    s_bPlayerConversationHappening = false;
    rng::fill(s_Conversation, GCTX_UNK);

    s_nCJBasicMood        = MOOD_UNK;
    s_nCJGangBanging      = -1;
    s_nCJFat              = -1;
    s_nCJWellDressed      = -1;
    s_nCJMoodOverrideTime = 0;

    s_NextSpeechSlot     = 0;
    s_bAllSpeechDisabled = false;
    s_bAPlayerSpeaking   = false;
    s_bForceAudible      = false;
}

// 0x4E4470
int16 CAEPedSpeechAudioEntity::GetSpecificSpeechContext(eGlobalSpeechContext gCtx, eAudioPedType pedAudioType) {
    assert(gCtx > GCTX_UNK);             // notsa
    assert(gCtx < GCTX_NUM);             // OG: return -1; (silent error)
    assert(pedAudioType < PED_TYPE_NUM); // OG: return -1; (silent error)
    assert(pedAudioType >= 0);           // notsa

    if (const auto* const ctxi = GetSpeechContextInfo(gCtx)) {
        return ctxi->SpecificSpeechContext[pedAudioType];
    }
    return -1;
}

// 0x4E3710
void CAEPedSpeechAudioEntity::Service() {
    s_bForceAudible = false;
    for (auto&& [i, ss] : notsa::enumerate(s_PedSpeechSlots)) {
        // Waiting for sound to load, and has loaded?
        if (ss.Status == CAEPedSpeechSlot::eStatus::LOADING && AEAudioHardware.IsSoundLoaded(ss.SoundBankID, ss.SoundID, SND_BANK_SLOT_SPEECH1 + i)) {
            ss.Status = CAEPedSpeechSlot::eStatus::WAITING;
        }

        // Sound is now loaded, waiting to be played
        if (ss.Status == CAEPedSpeechSlot::eStatus::WAITING) {
            if (ss.StartPlaybackTime >= CTimer::GetTimeInMS()) {
                if (const auto ae = ss.AudioEntity) {
                    ae->PlayLoadedSound();
                } else {
                    ss.Status = CAEPedSpeechSlot::eStatus::FREE;
                }
            }
        }

        // `PlayLoadedSound` above might've modified the status, must check it again (can't use switch for whole code)
        switch (ss.Status) {
        case CAEPedSpeechSlot::eStatus::REQUESTED:
        case CAEPedSpeechSlot::eStatus::PLAYING: {
            s_bForceAudible |= ss.ForceAudible;
        }
        }
    }
}

// 0x4E37B0
void CAEPedSpeechAudioEntity::Reset() {
    for (auto& time : gGlobalSpeechContextNextPlayTime) {
        time = CTimer::GetTimeInMS() + CAEAudioUtility::GetRandomNumberInRange(3000, 7000);
    }
    s_nCJMoodOverrideTime = 0;
}

// 0x4E37F0
bool CAEPedSpeechAudioEntity::ReservePedConversationSpeechSlots() {
    // Originally they had a loop here that continued (small optimzation)
    // But I don't care ;) Logic stays the same tho, as it's single threaded.
    const auto slotA = GetFreeSpeechSlot(),
               slotB = GetFreeSpeechSlot();

    if (slotA == -1 || slotB == -1) {
        return false;
    }

    const auto SetupSlot = [](int32 slot) {
        auto* const ss                   = &s_PedSpeechSlots[slot];
        ss->Status                       = CAEPedSpeechSlot::eStatus::RESERVED;
        ss->IsReservedForPedConversation = true;
    };
    SetupSlot(s_pConversationPedSlot1 = slotA);
    SetupSlot(s_pConversationPedSlot2 = slotB);

    return true;
}

// 0x4E3870
bool CAEPedSpeechAudioEntity::ReservePlayerConversationSpeechSlot() {
    const auto slot = GetFreeSpeechSlot();
    if (slot == -1) {
        return false;
    }
    s_pConversationPedSlot1             = slot;
    auto* const ss                      = &s_PedSpeechSlots[slot];
    ss->Status                          = CAEPedSpeechSlot::eStatus::RESERVED;
    ss->IsReservedForPlayerConversation = true;

    return true;
}

// 0x4E38C0
bool CAEPedSpeechAudioEntity::RequestPlayerConversation(CPed* ped) {
    if (s_bAllSpeechDisabled) {
        return false;
    }

    if (ped->m_pedSpeech.m_IsSpeechForScriptsDisabled || ped->m_pedSpeech.m_IsSpeechDisabled) {
        return false;
    }

    const auto player = FindPlayerPed();
    if (!player || player->m_pedSpeech.m_IsSpeechDisabled || player->m_pedSpeech.m_IsSpeechForScriptsDisabled) {
        return false;
    }

    if (   s_bPedConversationHappening
        || s_bPlayerConversationHappening
        || ped->GetPedTalking()
        || !ReservePlayerConversationSpeechSlot()
    ) {
        return false;
    }

    s_pPlayerConversationPed       = ped;
    s_bPlayerConversationHappening = true;

    return true;
}

// 0x4E3960
void CAEPedSpeechAudioEntity::ReleasePlayerConversation() {
    if (!s_bPlayerConversationHappening) {
        return;
    }
    s_bPlayerConversationHappening = false;
    if (s_pConversationPedSlot1 < 0) {
        return;
    }
    auto* const ss = &s_PedSpeechSlots[s_pConversationPedSlot1];
    switch (ss->Status) {
    case CAEPedSpeechSlot::eStatus::FREE:
    case CAEPedSpeechSlot::eStatus::RESERVED: {
        *ss = {};
    }
    }
    s_PedSpeechSlots[s_pConversationPedSlot1] = {};
    s_pConversationPedSlot1                   = -1;
    s_pPlayerConversationPed                  = nullptr;
}

// 0x4E3A00
void CAEPedSpeechAudioEntity::SetUpConversation() {
    rng::fill(s_Conversation, GCTX_NO_SPEECH);

    auto PushConvo = [i = 0](eGlobalSpeechContext gctx) mutable {
        s_Conversation[i++] = gctx;
    };

    const auto PushConvoForPeds = [&](eGlobalSpeechContext ifFemale, eGlobalSpeechContext ifMale) {
        const auto PushConvoForPed = [&](const CPed* p) {
            switch (p->m_nPedType) {
            case PED_TYPE_PROSTITUTE:
            case PED_TYPE_CIVFEMALE: PushConvo(ifFemale); break;
            default:                 PushConvo(ifMale);   break;
            }
        };
        PushConvoForPed(s_pConversationPed2); // yes, ped 2, then ped 1
        PushConvoForPed(s_pConversationPed1);
    };

    // Greeting
    PushConvoForPeds(GCTX_PCONV_GREET_FEM, GCTX_PCONV_GREET_MALE);

    // Other stuff
    const auto r = CAEAudioUtility::GetRandomNumberInRange(1, 10);
    if (r <= 8) { // Combined cases 1, -> 4 + 5, -> 8
        const auto hasInitialState = r <= 4;

        s_ConversationLength = hasInitialState ? 3 : 2;

        if (hasInitialState) { // For cases 1 -> 4 only
            const auto isGood = CGeneral::DoCoinFlip();
            PushConvo(isGood ?  GCTX_PCONV_STATE_GOOD :  GCTX_PCONV_STATE_BAD);
            PushConvo(isGood ?  GCTX_PCONV_AGREE_GOOD :  GCTX_PCONV_AGREE_BAD);
        }

        // A question
        PushConvo(GCTX_PCONV_QUESTION);

        // Whenever they agree with the answer (?)
        switch (CAEAudioUtility::GetRandomNumberInRange(0, 2)) {
        case 0: PushConvo(GCTX_PCONV_AGREE_GOOD); break;
        case 1: PushConvo(GCTX_PCONV_AGREE_BAD);  break;
        case 2: PushConvo(GCTX_PCONV_ANS_NO);     break;
        }

        // Part away (?)
        PushConvoForPeds(GCTX_PCONV_PART_FEM, GCTX_PCONV_PART_MALE);
    } else if (r <= 10) { // cases 9, 10
        s_ConversationLength = 1;

        PushConvo(CGeneral::DoCoinFlip() ?  GCTX_PCONV_STATE_GOOD :  GCTX_PCONV_STATE_BAD);
        PushConvo(GCTX_PCONV_DISMISS);
    } else {
        NOTSA_UNREACHABLE();
    }
}

// 0x4E3C60
eAudioPedType CAEPedSpeechAudioEntity::GetAudioPedType(const char* name) {
    static const auto mapping = notsa::make_mapping<std::string_view, eAudioPedType>({
        {"PED_TYPE_GEN",    PED_TYPE_GEN   },
        {"PED_TYPE_EMG",    PED_TYPE_EMG   },
        {"PED_TYPE_PLAYER", PED_TYPE_PLAYER},
        {"PED_TYPE_GANG",   PED_TYPE_GANG  },
        {"PED_TYPE_GFD",    PED_TYPE_GFD   },
        {"PED_TYPE_SPC",    PED_TYPE_SPC   },
    });
    return notsa::find_value_or(mapping, name, PED_TYPE_UNK);
}

// 0x4E3CD0
ePedSpeechVoiceS16 CAEPedSpeechAudioEntity::GetVoice(const char* name, eAudioPedTypeS16 type) {
    switch (type) {
    case PED_TYPE_GEN: {
        static const auto mapping = notsa::make_mapping<std::string_view, eGenSpeechVoices>({
            {"VOICE_GEN_BBDYG1", VOICE_GEN_BBDYG1}, {"VOICE_GEN_BBDYG2", VOICE_GEN_BBDYG2}, {"VOICE_GEN_BFORI", VOICE_GEN_BFORI}, {"VOICE_GEN_BFOST", VOICE_GEN_BFOST}, {"VOICE_GEN_BFYBE", VOICE_GEN_BFYBE}, {"VOICE_GEN_BFYBU", VOICE_GEN_BFYBU}, {"VOICE_GEN_BFYCRP", VOICE_GEN_BFYCRP}, {"VOICE_GEN_BFYPRO", VOICE_GEN_BFYPRO}, {"VOICE_GEN_BFYRI", VOICE_GEN_BFYRI}, {"VOICE_GEN_BFYST", VOICE_GEN_BFYST}, {"VOICE_GEN_BIKDRUG", VOICE_GEN_BIKDRUG}, {"VOICE_GEN_BIKERA", VOICE_GEN_BIKERA}, {"VOICE_GEN_BIKERB", VOICE_GEN_BIKERB}, {"VOICE_GEN_BMOCD", VOICE_GEN_BMOCD}, {"VOICE_GEN_BMORI", VOICE_GEN_BMORI}, {"VOICE_GEN_BMOSEC", VOICE_GEN_BMOSEC}, {"VOICE_GEN_BMOST", VOICE_GEN_BMOST}, {"VOICE_GEN_BMOTR1", VOICE_GEN_BMOTR1}, {"VOICE_GEN_BMYAP", VOICE_GEN_BMYAP}, {"VOICE_GEN_BMYBE", VOICE_GEN_BMYBE}, {"VOICE_GEN_BMYBOUN", VOICE_GEN_BMYBOUN}, {"VOICE_GEN_BMYBOX", VOICE_GEN_BMYBOX}, {"VOICE_GEN_BMYBU", VOICE_GEN_BMYBU}, {"VOICE_GEN_BMYCG", VOICE_GEN_BMYCG}, {"VOICE_GEN_BMYCON", VOICE_GEN_BMYCON}, {"VOICE_GEN_BMYCR", VOICE_GEN_BMYCR}, {"VOICE_GEN_BMYDJ", VOICE_GEN_BMYDJ}, {"VOICE_GEN_BMYDRUG", VOICE_GEN_BMYDRUG}, {"VOICE_GEN_BMYMOUN", VOICE_GEN_BMYMOUN}, {"VOICE_GEN_BMYPOL1", VOICE_GEN_BMYPOL1}, {"VOICE_GEN_BMYPOL2", VOICE_GEN_BMYPOL2}, {"VOICE_GEN_BMYRI", VOICE_GEN_BMYRI}, {"VOICE_GEN_BMYST", VOICE_GEN_BMYST}, {"VOICE_GEN_BYMPI", VOICE_GEN_BYMPI}, {"VOICE_GEN_CWFOFR", VOICE_GEN_CWFOFR}, {"VOICE_GEN_CWFOHB", VOICE_GEN_CWFOHB}, {"VOICE_GEN_CWFYFR1", VOICE_GEN_CWFYFR1}, {"VOICE_GEN_CWFYFR2", VOICE_GEN_CWFYFR2}, {"VOICE_GEN_CWFYHB1", VOICE_GEN_CWFYHB1}, {"VOICE_GEN_CWMOFR1", VOICE_GEN_CWMOFR1}, {"VOICE_GEN_CWMOHB1", VOICE_GEN_CWMOHB1}, {"VOICE_GEN_CWMOHB2", VOICE_GEN_CWMOHB2}, {"VOICE_GEN_CWMYFR", VOICE_GEN_CWMYFR}, {"VOICE_GEN_CWMYHB1", VOICE_GEN_CWMYHB1}, {"VOICE_GEN_CWMYHB2", VOICE_GEN_CWMYHB2}, {"VOICE_GEN_DNFOLC1", VOICE_GEN_DNFOLC1}, {"VOICE_GEN_DNFOLC2", VOICE_GEN_DNFOLC2}, {"VOICE_GEN_DNFYLC", VOICE_GEN_DNFYLC}, {"VOICE_GEN_DNMOLC1", VOICE_GEN_DNMOLC1}, {"VOICE_GEN_DNMOLC2", VOICE_GEN_DNMOLC2}, {"VOICE_GEN_DNMYLC", VOICE_GEN_DNMYLC}, {"VOICE_GEN_DWFOLC", VOICE_GEN_DWFOLC}, {"VOICE_GEN_DWFYLC1", VOICE_GEN_DWFYLC1}, {"VOICE_GEN_DWFYLC2", VOICE_GEN_DWFYLC2}, {"VOICE_GEN_DWMOLC1", VOICE_GEN_DWMOLC1}, {"VOICE_GEN_DWMOLC2", VOICE_GEN_DWMOLC2}, {"VOICE_GEN_DWMYLC1", VOICE_GEN_DWMYLC1}, {"VOICE_GEN_DWMYLC2", VOICE_GEN_DWMYLC2}, {"VOICE_GEN_HFORI", VOICE_GEN_HFORI}, {"VOICE_GEN_HFOST", VOICE_GEN_HFOST}, {"VOICE_GEN_HFYBE", VOICE_GEN_HFYBE}, {"VOICE_GEN_HFYPRO", VOICE_GEN_HFYPRO}, {"VOICE_GEN_HFYRI", VOICE_GEN_HFYRI}, {"VOICE_GEN_HFYST", VOICE_GEN_HFYST}, {"VOICE_GEN_HMORI", VOICE_GEN_HMORI}, {"VOICE_GEN_HMOST", VOICE_GEN_HMOST}, {"VOICE_GEN_HMYBE", VOICE_GEN_HMYBE}, {"VOICE_GEN_HMYCM", VOICE_GEN_HMYCM}, {"VOICE_GEN_HMYCR", VOICE_GEN_HMYCR}, {"VOICE_GEN_HMYDRUG", VOICE_GEN_HMYDRUG}, {"VOICE_GEN_HMYRI", VOICE_GEN_HMYRI}, {"VOICE_GEN_HMYST", VOICE_GEN_HMYST}, {"VOICE_GEN_IMYST", VOICE_GEN_IMYST}, {"VOICE_GEN_IRFYST", VOICE_GEN_IRFYST}, {"VOICE_GEN_IRMYST", VOICE_GEN_IRMYST}, {"VOICE_GEN_MAFFA", VOICE_GEN_MAFFA}, {"VOICE_GEN_MAFFB", VOICE_GEN_MAFFB}, {"VOICE_GEN_MALE01", VOICE_GEN_MALE01}, {"VOICE_GEN_NOVOICE", VOICE_GEN_NOVOICE}, {"VOICE_GEN_OFORI", VOICE_GEN_OFORI}, {"VOICE_GEN_OFOST", VOICE_GEN_OFOST}, {"VOICE_GEN_OFYRI", VOICE_GEN_OFYRI}, {"VOICE_GEN_OFYST", VOICE_GEN_OFYST}, {"VOICE_GEN_OMOBOAT", VOICE_GEN_OMOBOAT}, {"VOICE_GEN_OMOKUNG", VOICE_GEN_OMOKUNG}, {"VOICE_GEN_OMORI", VOICE_GEN_OMORI}, {"VOICE_GEN_OMOST", VOICE_GEN_OMOST}, {"VOICE_GEN_OMYRI", VOICE_GEN_OMYRI}, {"VOICE_GEN_OMYST", VOICE_GEN_OMYST}, {"VOICE_GEN_SBFORI", VOICE_GEN_SBFORI}, {"VOICE_GEN_SBFOST", VOICE_GEN_SBFOST}, {"VOICE_GEN_SBFYPRO", VOICE_GEN_SBFYPRO}, {"VOICE_GEN_SBFYRI", VOICE_GEN_SBFYRI}, {"VOICE_GEN_SBFYST", VOICE_GEN_SBFYST}, {"VOICE_GEN_SBFYSTR", VOICE_GEN_SBFYSTR}, {"VOICE_GEN_SBMOCD", VOICE_GEN_SBMOCD}, {"VOICE_GEN_SBMORI", VOICE_GEN_SBMORI}, {"VOICE_GEN_SBMOST", VOICE_GEN_SBMOST}, {"VOICE_GEN_SBMOTR1", VOICE_GEN_SBMOTR1}, {"VOICE_GEN_SBMOTR2", VOICE_GEN_SBMOTR2}, {"VOICE_GEN_SBMYCR", VOICE_GEN_SBMYCR}, {"VOICE_GEN_SBMYRI", VOICE_GEN_SBMYRI}, {"VOICE_GEN_SBMYST", VOICE_GEN_SBMYST}, {"VOICE_GEN_SBMYTR3", VOICE_GEN_SBMYTR3}, {"VOICE_GEN_SFYPRO", VOICE_GEN_SFYPRO}, {"VOICE_GEN_SHFYPRO", VOICE_GEN_SHFYPRO}, {"VOICE_GEN_SHMYCR", VOICE_GEN_SHMYCR}, {"VOICE_GEN_SMYST", VOICE_GEN_SMYST}, {"VOICE_GEN_SMYST2", VOICE_GEN_SMYST2}, {"VOICE_GEN_SOFORI", VOICE_GEN_SOFORI}, {"VOICE_GEN_SOFOST", VOICE_GEN_SOFOST}, {"VOICE_GEN_SOFYBU", VOICE_GEN_SOFYBU}, {"VOICE_GEN_SOFYRI", VOICE_GEN_SOFYRI}, {"VOICE_GEN_SOFYST", VOICE_GEN_SOFYST}, {"VOICE_GEN_SOMOBU", VOICE_GEN_SOMOBU}, {"VOICE_GEN_SOMORI", VOICE_GEN_SOMORI}, {"VOICE_GEN_SOMOST", VOICE_GEN_SOMOST}, {"VOICE_GEN_SOMYAP", VOICE_GEN_SOMYAP}, {"VOICE_GEN_SOMYBU", VOICE_GEN_SOMYBU}, {"VOICE_GEN_SOMYRI", VOICE_GEN_SOMYRI}, {"VOICE_GEN_SOMYST", VOICE_GEN_SOMYST}, {"VOICE_GEN_SWFOPRO", VOICE_GEN_SWFOPRO}, {"VOICE_GEN_SWFORI", VOICE_GEN_SWFORI}, {"VOICE_GEN_SWFOST", VOICE_GEN_SWFOST}, {"VOICE_GEN_SWFYRI", VOICE_GEN_SWFYRI}, {"VOICE_GEN_SWFYST", VOICE_GEN_SWFYST}, {"VOICE_GEN_SWFYSTR", VOICE_GEN_SWFYSTR}, {"VOICE_GEN_SWMOCD", VOICE_GEN_SWMOCD}, {"VOICE_GEN_SWMORI", VOICE_GEN_SWMORI}, {"VOICE_GEN_SWMOST", VOICE_GEN_SWMOST}, {"VOICE_GEN_SWMOTR1", VOICE_GEN_SWMOTR1}, {"VOICE_GEN_SWMOTR2", VOICE_GEN_SWMOTR2}, {"VOICE_GEN_SWMOTR3", VOICE_GEN_SWMOTR3}, {"VOICE_GEN_SWMOTR4", VOICE_GEN_SWMOTR4}, {"VOICE_GEN_SWMOTR5", VOICE_GEN_SWMOTR5}, {"VOICE_GEN_SWMYCR", VOICE_GEN_SWMYCR}, {"VOICE_GEN_SWMYHP1", VOICE_GEN_SWMYHP1}, {"VOICE_GEN_SWMYHP2", VOICE_GEN_SWMYHP2}, {"VOICE_GEN_SWMYRI", VOICE_GEN_SWMYRI}, {"VOICE_GEN_SWMYST", VOICE_GEN_SWMYST}, {"VOICE_GEN_VBFYPRO", VOICE_GEN_VBFYPRO}, {"VOICE_GEN_VBFYST2", VOICE_GEN_VBFYST2}, {"VOICE_GEN_VBMOCD", VOICE_GEN_VBMOCD}, {"VOICE_GEN_VBMYCR", VOICE_GEN_VBMYCR}, {"VOICE_GEN_VBMYELV", VOICE_GEN_VBMYELV}, {"VOICE_GEN_VHFYPRO", VOICE_GEN_VHFYPRO}, {"VOICE_GEN_VHFYST3", VOICE_GEN_VHFYST3}, {"VOICE_GEN_VHMYCR", VOICE_GEN_VHMYCR}, {"VOICE_GEN_VHMYELV", VOICE_GEN_VHMYELV}, {"VOICE_GEN_VIMYELV", VOICE_GEN_VIMYELV}, {"VOICE_GEN_VWFYPRO", VOICE_GEN_VWFYPRO}, {"VOICE_GEN_VWFYST1", VOICE_GEN_VWFYST1}, {"VOICE_GEN_VWFYWAI", VOICE_GEN_VWFYWAI}, {"VOICE_GEN_VWMOTR1", VOICE_GEN_VWMOTR1}, {"VOICE_GEN_VWMOTR2", VOICE_GEN_VWMOTR2}, {"VOICE_GEN_VWMYAP", VOICE_GEN_VWMYAP}, {"VOICE_GEN_VWMYBJD", VOICE_GEN_VWMYBJD}, {"VOICE_GEN_VWMYCD", VOICE_GEN_VWMYCD}, {"VOICE_GEN_VWMYCR", VOICE_GEN_VWMYCR}, {"VOICE_GEN_WFOPJ", VOICE_GEN_WFOPJ}, {"VOICE_GEN_WFORI", VOICE_GEN_WFORI}, {"VOICE_GEN_WFOST", VOICE_GEN_WFOST}, {"VOICE_GEN_WFYBE", VOICE_GEN_WFYBE}, {"VOICE_GEN_WFYBU", VOICE_GEN_WFYBU}, {"VOICE_GEN_WFYCRK", VOICE_GEN_WFYCRK}, {"VOICE_GEN_WFYCRP", VOICE_GEN_WFYCRP}, {"VOICE_GEN_WFYJG", VOICE_GEN_WFYJG}, {"VOICE_GEN_WFYLG", VOICE_GEN_WFYLG}, {"VOICE_GEN_WFYPRO", VOICE_GEN_WFYPRO}, {"VOICE_GEN_WFYRI", VOICE_GEN_WFYRI}, {"VOICE_GEN_WFYRO", VOICE_GEN_WFYRO}, {"VOICE_GEN_WFYST", VOICE_GEN_WFYST}, {"VOICE_GEN_WFYSTEW", VOICE_GEN_WFYSTEW}, {"VOICE_GEN_WMOMIB", VOICE_GEN_WMOMIB}, {"VOICE_GEN_WMOPJ", VOICE_GEN_WMOPJ}, {"VOICE_GEN_WMOPREA", VOICE_GEN_WMOPREA}, {"VOICE_GEN_WMORI", VOICE_GEN_WMORI}, {"VOICE_GEN_WMOSCI", VOICE_GEN_WMOSCI}, {"VOICE_GEN_WMOST", VOICE_GEN_WMOST}, {"VOICE_GEN_WMOTR1", VOICE_GEN_WMOTR1}, {"VOICE_GEN_WMYBE", VOICE_GEN_WMYBE}, {"VOICE_GEN_WMYBMX", VOICE_GEN_WMYBMX}, {"VOICE_GEN_WMYBOUN", VOICE_GEN_WMYBOUN}, {"VOICE_GEN_WMYBOX", VOICE_GEN_WMYBOX}, {"VOICE_GEN_WMYBP", VOICE_GEN_WMYBP}, {"VOICE_GEN_WMYBU", VOICE_GEN_WMYBU}, {"VOICE_GEN_WMYCD1", VOICE_GEN_WMYCD1}, {"VOICE_GEN_WMYCD2", VOICE_GEN_WMYCD2}, {"VOICE_GEN_WMYCH", VOICE_GEN_WMYCH}, {"VOICE_GEN_WMYCON", VOICE_GEN_WMYCON}, {"VOICE_GEN_WMYCONB", VOICE_GEN_WMYCONB}, {"VOICE_GEN_WMYCR", VOICE_GEN_WMYCR}, {"VOICE_GEN_WMYDRUG", VOICE_GEN_WMYDRUG}, {"VOICE_GEN_WMYGAR", VOICE_GEN_WMYGAR}, {"VOICE_GEN_WMYGOL1", VOICE_GEN_WMYGOL1}, {"VOICE_GEN_WMYGOL2", VOICE_GEN_WMYGOL2}, {"VOICE_GEN_WMYJG", VOICE_GEN_WMYJG}, {"VOICE_GEN_WMYLG", VOICE_GEN_WMYLG}, {"VOICE_GEN_WMYMECH", VOICE_GEN_WMYMECH}, {"VOICE_GEN_WMYMOUN", VOICE_GEN_WMYMOUN}, {"VOICE_GEN_WMYPLT", VOICE_GEN_WMYPLT}, {"VOICE_GEN_WMYRI", VOICE_GEN_WMYRI}, {"VOICE_GEN_WMYRO", VOICE_GEN_WMYRO}, {"VOICE_GEN_WMYSGRD", VOICE_GEN_WMYSGRD}, {"VOICE_GEN_WMYSKAT", VOICE_GEN_WMYSKAT}, {"VOICE_GEN_WMYST", VOICE_GEN_WMYST}, {"VOICE_GEN_WMYTX1", VOICE_GEN_WMYTX1}, {"VOICE_GEN_WMYTX2", VOICE_GEN_WMYTX2}, {"VOICE_GEN_WMYVA", VOICE_GEN_WMYVA}
        });
        return notsa::find_value_or(mapping, name, -1);
    }
    case PED_TYPE_EMG: {
        static const auto mapping = notsa::make_mapping<std::string_view, eEmgSpeechVoices>({
            {"VOICE_EMG_ARMY1", VOICE_EMG_ARMY1}, {"VOICE_EMG_ARMY2", VOICE_EMG_ARMY2}, {"VOICE_EMG_ARMY3", VOICE_EMG_ARMY3}, {"VOICE_EMG_EMT1", VOICE_EMG_EMT1}, {"VOICE_EMG_EMT2", VOICE_EMG_EMT2}, {"VOICE_EMG_EMT3", VOICE_EMG_EMT3}, {"VOICE_EMG_EMT4", VOICE_EMG_EMT4}, {"VOICE_EMG_EMT5", VOICE_EMG_EMT5}, {"VOICE_EMG_FBI2", VOICE_EMG_FBI2}, {"VOICE_EMG_FBI3", VOICE_EMG_FBI3}, {"VOICE_EMG_FBI4", VOICE_EMG_FBI4}, {"VOICE_EMG_FBI5", VOICE_EMG_FBI5}, {"VOICE_EMG_FBI6", VOICE_EMG_FBI6}, {"VOICE_EMG_LAPD1", VOICE_EMG_LAPD1}, {"VOICE_EMG_LAPD2", VOICE_EMG_LAPD2}, {"VOICE_EMG_LAPD3", VOICE_EMG_LAPD3}, {"VOICE_EMG_LAPD4", VOICE_EMG_LAPD4}, {"VOICE_EMG_LAPD5", VOICE_EMG_LAPD5}, {"VOICE_EMG_LAPD6", VOICE_EMG_LAPD6}, {"VOICE_EMG_LAPD7", VOICE_EMG_LAPD7}, {"VOICE_EMG_LAPD8", VOICE_EMG_LAPD8}, {"VOICE_EMG_LVPD1", VOICE_EMG_LVPD1}, {"VOICE_EMG_LVPD2", VOICE_EMG_LVPD2}, {"VOICE_EMG_LVPD3", VOICE_EMG_LVPD3}, {"VOICE_EMG_LVPD4", VOICE_EMG_LVPD4}, {"VOICE_EMG_LVPD5", VOICE_EMG_LVPD5}, {"VOICE_EMG_MCOP1", VOICE_EMG_MCOP1}, {"VOICE_EMG_MCOP2", VOICE_EMG_MCOP2}, {"VOICE_EMG_MCOP3", VOICE_EMG_MCOP3}, {"VOICE_EMG_MCOP4", VOICE_EMG_MCOP4}, {"VOICE_EMG_MCOP5", VOICE_EMG_MCOP5}, {"VOICE_EMG_MCOP6", VOICE_EMG_MCOP6}, {"VOICE_EMG_PULASKI", VOICE_EMG_PULASKI}, {"VOICE_EMG_RCOP1", VOICE_EMG_RCOP1}, {"VOICE_EMG_RCOP2", VOICE_EMG_RCOP2}, {"VOICE_EMG_RCOP3", VOICE_EMG_RCOP3}, {"VOICE_EMG_RCOP4", VOICE_EMG_RCOP4}, {"VOICE_EMG_SFPD1", VOICE_EMG_SFPD1}, {"VOICE_EMG_SFPD2", VOICE_EMG_SFPD2}, {"VOICE_EMG_SFPD3", VOICE_EMG_SFPD3}, {"VOICE_EMG_SFPD4", VOICE_EMG_SFPD4}, {"VOICE_EMG_SFPD5", VOICE_EMG_SFPD5}, {"VOICE_EMG_SWAT1", VOICE_EMG_SWAT1}, {"VOICE_EMG_SWAT2", VOICE_EMG_SWAT2}, {"VOICE_EMG_SWAT4", VOICE_EMG_SWAT4}, {"VOICE_EMG_SWAT6", VOICE_EMG_SWAT6},
        });
        return notsa::find_value_or(mapping, name, -1);
    }
    case PED_TYPE_PLAYER: {
        static const auto mapping = notsa::make_mapping<std::string_view, ePlySpeechVoices>({
            {"VOICE_PLY_AG", VOICE_PLY_AG}, {"VOICE_PLY_AG2", VOICE_PLY_AG2}, {"VOICE_PLY_AR", VOICE_PLY_AR}, {"VOICE_PLY_AR2", VOICE_PLY_AR2}, {"VOICE_PLY_CD", VOICE_PLY_CD}, {"VOICE_PLY_CD2", VOICE_PLY_CD2}, {"VOICE_PLY_CF", VOICE_PLY_CF}, {"VOICE_PLY_CF2", VOICE_PLY_CF2}, {"VOICE_PLY_CG", VOICE_PLY_CG}, {"VOICE_PLY_CG2", VOICE_PLY_CG2}, {"VOICE_PLY_CR", VOICE_PLY_CR}, {"VOICE_PLY_CR2", VOICE_PLY_CR2}, {"VOICE_PLY_PG", VOICE_PLY_PG}, {"VOICE_PLY_PG2", VOICE_PLY_PG2}, {"VOICE_PLY_PR", VOICE_PLY_PR}, {"VOICE_PLY_PR2", VOICE_PLY_PR2}, {"VOICE_PLY_WG", VOICE_PLY_WG}, {"VOICE_PLY_WG2", VOICE_PLY_WG2}, {"VOICE_PLY_WR", VOICE_PLY_WR}, {"VOICE_PLY_WR2", VOICE_PLY_WR2},
        });
        return notsa::find_value_or(mapping, name, -1);
    }
    case PED_TYPE_GANG: {
        static const auto mapping = notsa::make_mapping<std::string_view, eGngSpeechVoices>({
            {"VOICE_GNG_BALLAS1", VOICE_GNG_BALLAS1}, {"VOICE_GNG_BALLAS2", VOICE_GNG_BALLAS2}, {"VOICE_GNG_BALLAS3", VOICE_GNG_BALLAS3}, {"VOICE_GNG_BALLAS4", VOICE_GNG_BALLAS4}, {"VOICE_GNG_BALLAS5", VOICE_GNG_BALLAS5}, {"VOICE_GNG_BIG_BEAR", VOICE_GNG_BIG_BEAR}, {"VOICE_GNG_CESAR", VOICE_GNG_CESAR}, {"VOICE_GNG_DNB1", VOICE_GNG_DNB1}, {"VOICE_GNG_DNB2", VOICE_GNG_DNB2}, {"VOICE_GNG_DNB3", VOICE_GNG_DNB3}, {"VOICE_GNG_DNB5", VOICE_GNG_DNB5}, {"VOICE_GNG_DWAINE", VOICE_GNG_DWAINE}, {"VOICE_GNG_FAM1", VOICE_GNG_FAM1}, {"VOICE_GNG_FAM2", VOICE_GNG_FAM2}, {"VOICE_GNG_FAM3", VOICE_GNG_FAM3}, {"VOICE_GNG_FAM4", VOICE_GNG_FAM4}, {"VOICE_GNG_FAM5", VOICE_GNG_FAM5}, {"VOICE_GNG_JIZZY", VOICE_GNG_JIZZY}, {"VOICE_GNG_LSV1", VOICE_GNG_LSV1}, {"VOICE_GNG_LSV2", VOICE_GNG_LSV2}, {"VOICE_GNG_LSV3", VOICE_GNG_LSV3}, {"VOICE_GNG_LSV4", VOICE_GNG_LSV4}, {"VOICE_GNG_LSV5", VOICE_GNG_LSV5}, {"VOICE_GNG_MACCER", VOICE_GNG_MACCER}, {"VOICE_GNG_MAFBOSS", VOICE_GNG_MAFBOSS}, {"VOICE_GNG_OGLOC", VOICE_GNG_OGLOC}, {"VOICE_GNG_RYDER", VOICE_GNG_RYDER}, {"VOICE_GNG_SFR1", VOICE_GNG_SFR1}, {"VOICE_GNG_SFR2", VOICE_GNG_SFR2}, {"VOICE_GNG_SFR3", VOICE_GNG_SFR3}, {"VOICE_GNG_SFR4", VOICE_GNG_SFR4}, {"VOICE_GNG_SFR5", VOICE_GNG_SFR5}, {"VOICE_GNG_SMOKE", VOICE_GNG_SMOKE}, {"VOICE_GNG_STRI1", VOICE_GNG_STRI1}, {"VOICE_GNG_STRI2", VOICE_GNG_STRI2}, {"VOICE_GNG_STRI4", VOICE_GNG_STRI4}, {"VOICE_GNG_STRI5", VOICE_GNG_STRI5}, {"VOICE_GNG_SWEET", VOICE_GNG_SWEET}, {"VOICE_GNG_TBONE", VOICE_GNG_TBONE}, {"VOICE_GNG_TORENO", VOICE_GNG_TORENO}, {"VOICE_GNG_TRUTH", VOICE_GNG_TRUTH}, {"VOICE_GNG_VLA1", VOICE_GNG_VLA1}, {"VOICE_GNG_VLA2", VOICE_GNG_VLA2}, {"VOICE_GNG_VLA3", VOICE_GNG_VLA3}, {"VOICE_GNG_VLA4", VOICE_GNG_VLA4}, {"VOICE_GNG_VLA5", VOICE_GNG_VLA5}, {"VOICE_GNG_VMAFF1", VOICE_GNG_VMAFF1}, {"VOICE_GNG_VMAFF2", VOICE_GNG_VMAFF2}, {"VOICE_GNG_VMAFF3", VOICE_GNG_VMAFF3}, {"VOICE_GNG_VMAFF4", VOICE_GNG_VMAFF4}, {"VOICE_GNG_VMAFF5", VOICE_GNG_VMAFF5}, {"VOICE_GNG_WOOZIE", VOICE_GNG_WOOZIE},
        });
        return notsa::find_value_or(mapping, name, -1);
    }
    case PED_TYPE_GFD: {
        static const auto mapping = notsa::make_mapping<std::string_view, eGfdSpeechVoices>({
            {"VOICE_GFD_BARBARA", VOICE_GFD_BARBARA}, {"VOICE_GFD_BMOBAR", VOICE_GFD_BMOBAR}, {"VOICE_GFD_BMYBARB", VOICE_GFD_BMYBARB}, {"VOICE_GFD_BMYTATT", VOICE_GFD_BMYTATT}, {"VOICE_GFD_CATALINA", VOICE_GFD_CATALINA}, {"VOICE_GFD_DENISE", VOICE_GFD_DENISE}, {"VOICE_GFD_HELENA", VOICE_GFD_HELENA}, {"VOICE_GFD_KATIE", VOICE_GFD_KATIE}, {"VOICE_GFD_MICHELLE", VOICE_GFD_MICHELLE}, {"VOICE_GFD_MILLIE", VOICE_GFD_MILLIE}, {"VOICE_GFD_POL_ANN", VOICE_GFD_POL_ANN}, {"VOICE_GFD_WFYBURG", VOICE_GFD_WFYBURG}, {"VOICE_GFD_WFYCLOT", VOICE_GFD_WFYCLOT}, {"VOICE_GFD_WMYAMMO", VOICE_GFD_WMYAMMO}, {"VOICE_GFD_WMYBARB", VOICE_GFD_WMYBARB}, {"VOICE_GFD_WMYBELL", VOICE_GFD_WMYBELL}, {"VOICE_GFD_WMYCLOT", VOICE_GFD_WMYCLOT}, {"VOICE_GFD_WMYPIZZ", VOICE_GFD_WMYPIZZ},
        });
        return notsa::find_value_or(mapping, name, -1);
    }
    default:
        NOTSA_UNREACHABLE();
    }
}

// 0x4E3EB0
void CAEPedSpeechAudioEntity::DisableAllPedSpeech() {
    s_bAllSpeechDisabled = true;
}

// 0x4E44F0
bool CAEPedSpeechAudioEntity::IsGlobalContextPain(int16 globalCtx) {
    return GCTX_PAIN_START < globalCtx && globalCtx < GCTX_PAIN_END;
}

// 0x4E3ED0
void CAEPedSpeechAudioEntity::SetCJMood(eCJMood basicMood, uint32 overrideTimeMS, int16 isGangBanging, int16 isFat, int16 isWellDressed) {
    s_nCJMoodOverrideTime = CTimer::GetTimeInMS() + overrideTimeMS;
    s_nCJBasicMood  = [=]{
        switch (basicMood) {
        case MOOD_AR:
        case MOOD_CR:
        case MOOD_PR:
        case MOOD_WR: return basicMood;
        default:      return MOOD_UNK;
        }
    }();
    s_nCJGangBanging = isGangBanging;
    s_nCJFat         = isFat;
    s_nCJWellDressed = isWellDressed;
}

// 0x4E3EC0
void CAEPedSpeechAudioEntity::EnableAllPedSpeech() {
    s_bAllSpeechDisabled = false;
}

// 0x4E4270
bool CAEPedSpeechAudioEntity::IsCJDressedInForGangSpeech() {
    static constexpr struct {
        eClothesTexturePart ClothesPart;
        const char*         TexName;
    } GANG_SPEECH_CLOTHES[] = {
        { CLOTHES_TEXTURE_TORSO,   "hoodyagreen" },
        { CLOTHES_TEXTURE_TORSO,   "shirtbgang"  },
        { CLOTHES_TEXTURE_LEGS,    "tracktrgang" },
        { CLOTHES_TEXTURE_LEGS,    "denimsgang"  },
        { CLOTHES_TEXTURE_HATS,    "bandgang"    },
        { CLOTHES_TEXTURE_HATS,    "hockey"      },
        { CLOTHES_TEXTURE_HATS,    "capgang"     },
        { CLOTHES_TEXTURE_HATS,    "capgangback" },
        { CLOTHES_TEXTURE_HATS,    "capgangside" },
        { CLOTHES_TEXTURE_HATS,    "capgangover" },
        { CLOTHES_TEXTURE_HATS,    "capgangup"   },
        { CLOTHES_TEXTURE_GLASSES, "bandred3"    },
        { CLOTHES_TEXTURE_GLASSES, "bandblue3"   },
        { CLOTHES_TEXTURE_GLASSES, "bandgang3"   },
        { CLOTHES_TEXTURE_GLASSES, "bandblack3"  },
    };

    if (!FindPlayerPed(PED_TYPE_PLAYER1)) {
        return false;
    }

    if (CGameLogic::FindCityClosestToPoint(FindPlayerCoors()) != LEVEL_NAME_LOS_SANTOS) {
        return false;
    }

    return rng::any_of(GANG_SPEECH_CLOTHES, [pcd = FindPlayerPed()->GetClothesDesc()](auto& gc) {
        return pcd->m_anTextureKeys[gc.ClothesPart] == CKeyGen::GetUppercaseKey(gc.TexName);
    });
}

// 0x4E4260
int8 CAEPedSpeechAudioEntity::GetSexForSpecialPed(uint32 a1) {
    return 1;
}

// 0x4E46B0
bool CAEPedSpeechAudioEntity::IsGlobalContextImportantForWidescreen(int16 gCtx) {
    switch (m_PedAudioType) {
    case PED_TYPE_GFD:
    case PED_TYPE_PLAYER:
        return true;
    }
    switch (gCtx) {
    case GCTX_ARREST:
    case GCTX_ARRESTED:
    case GCTX_HAVING_SEX:
        return true;
    }
    return false;
}

// 0x4E47E0
int16 CAEPedSpeechAudioEntity::GetRepeatTime(eGlobalSpeechContext gCtx) {
    assert(gCtx < GCTX_NUM); // OG: return 0

    if (const auto* const ctxi = GetSpeechContextInfo(gCtx)) {
        return ctxi->RepeatTime;
    }
    return 0;
}

// 0x4E4840
void CAEPedSpeechAudioEntity::LoadAndPlaySpeech(uint32 playbackTimeOffsetMS) {
    auto& ss = GetMySpeechSlot();
    switch (ss.Status) {
    case CAEPedSpeechSlot::eStatus::FREE:
    case CAEPedSpeechSlot::eStatus::RESERVED:
        break;
    default:
        return;
    }

    AEAudioHardware.LoadSound(m_BankID, m_SoundID, SND_BANK_SLOT_SPEECH1 + m_PedSpeechSlotID); // TODO: Helper
    ss.Status            = CAEPedSpeechSlot::eStatus::LOADING;
    ss.SoundBankID       = m_BankID;
    ss.SoundID           = m_SoundID;
    ss.AudioEntity       = this;
    ss.StartPlaybackTime = CTimer::GetTimeInMS() + playbackTimeOffsetMS;
    ss.PedAudioType      = m_PedAudioType;
    ss.GCtx              = m_LastGCtx;
    ss.ForceAudible      = m_IsForcedAudible;
}

// 0x4E49B0
int32 CAEPedSpeechAudioEntity::GetNumSlotsPlayingContext(int16 context) {
    return rng::count_if(s_PedSpeechSlots, [&](CAEPedSpeechSlot& speech) {
        return speech.Status != CAEPedSpeechSlot::eStatus::FREE && speech.GCtx == context;
    });
}

// 0x4E49E0
uint32 CAEPedSpeechAudioEntity::GetNextPlayTime(eGlobalSpeechContext gCtx) {
    assert(gCtx < GCTX_NUM); // OG: `return 0;`

    return GetNextPlayTimeRef(gCtx);
}

// 0x4E4A20
void CAEPedSpeechAudioEntity::SetNextPlayTime(eGlobalSpeechContext gCtx) {
    assert(gCtx < GCTX_NUM); // OG: `return;`

    if (const auto* const ctxi = GetSpeechContextInfo(gCtx)) {
        GetNextPlayTimeRef(gCtx) = CTimer::GetTimeInMS() + ctxi->RepeatTime + CAEAudioUtility::GetRandomNumberInRange(1, 1000);
    }
}

// 0x4E56D0
void CAEPedSpeechAudioEntity::DisablePedSpeech(int16 a1) {
    if (m_IsInitialized) {
        m_IsSpeechDisabled = true;
        if (a1)
            StopCurrentSpeech();
    }
}

// 0x4E5700
void CAEPedSpeechAudioEntity::DisablePedSpeechForScriptSpeech(int16 a1) {
    if (m_IsInitialized) {
        m_IsSpeechForScriptsDisabled = true;
        if (a1)
            StopCurrentSpeech();
    }
}

// 0x4E5730
int8 CAEPedSpeechAudioEntity::CanPedSayGlobalContext(int16 a2) {
    return plugin::CallMethodAndReturn<int8, 0x4E5730>(this, a2);
}

// 0x4E58C0
int8 CAEPedSpeechAudioEntity::GetVoiceAndTypeFromModel(eModelID modelId) {
    auto* const mi = CModelInfo::GetModelInfo(modelId)->AsPedModelInfoPtr();
    if (mi->m_nPedAudioType < 0 || mi->m_nPedAudioType >= PED_TYPE_NUM) {
        return 0;
    }

    if (mi->m_nPedAudioType == PED_TYPE_SPC) {
        return GetVoiceAndTypeForSpecialPed(mi->m_nKey);
    }

    m_VoiceID = mi->m_nVoiceId;
    if (m_VoiceID == -1) {
        return 0;
    }

    mi->IncrementVoice();

    return 1;
}

// 0x4E5920
int16 CAEPedSpeechAudioEntity::GetSoundAndBankIDs(int16 phraseId, int16* a3) {
    return plugin::CallMethodAndReturn<int16, 0x4E5920, CAEPedSpeechAudioEntity*, int16, int16*>(this, phraseId, a3);
}

// 0x4E5F10
bool CAEPedSpeechAudioEntity::CanWePlayGlobalSpeechContext(int16 a2) {
    return plugin::CallMethodAndReturn<bool, 0x4E5F10, CAEPedSpeechAudioEntity*, int16>(this, a2);
}

// 0x4E6550
int16 CAEPedSpeechAudioEntity::AddSayEvent(eAudioEvents audioEvent, int16 phraseId, uint32 a4, float a5, uint8 a6, uint8 a7, uint8 a8) {
    return plugin::CallMethodAndReturn<int16, 0x4E6550, CAEPedSpeechAudioEntity*, int32, int16, uint32, float, uint8, uint8>(this, audioEvent, phraseId, a4, a5, a6, a7, a8);
}

// 0x4E68D0
void CAEPedSpeechAudioEntity::Initialise(CEntity* ped) {
    plugin::CallMethod<0x4E68D0, CAEPedSpeechAudioEntity*, CEntity*>(this, ped);
}

// 0x4E69E0
bool CAEPedSpeechAudioEntity::CanPedHoldConversation() {
    return plugin::CallMethodAndReturn<bool, 0x4E69E0, CAEPedSpeechAudioEntity*>(this);
}

// 0x4E4510
bool CAEPedSpeechAudioEntity::IsGlobalContextImportantForStreaming(int16 a1) {
    return plugin::CallMethodAndReturn<bool, 0x4E4510, CAEPedSpeechAudioEntity*, int16>(this, a1);
}

// 0x4E3F70
void CAEPedSpeechAudioEntity::EnablePedSpeech() {
    if (m_IsInitialized)
        m_IsSpeechDisabled = false;
}

// 0x4E3F90
void CAEPedSpeechAudioEntity::EnablePedSpeechForScriptSpeech() {
    if (m_IsInitialized)
        m_IsSpeechForScriptsDisabled = false;
}

// 0x4E3FB0
void CAEPedSpeechAudioEntity::StopCurrentSpeech() {
    plugin::CallMethod<0x4E3FB0, CAEPedSpeechAudioEntity*>(this);
}

// 0x4E4400
int8 CAEPedSpeechAudioEntity::GetSoundAndBankIDsForScriptedSpeech(int32 a2) {
    return plugin::CallMethodAndReturn<int8, 0x4E4400, CAEPedSpeechAudioEntity*, int32>(this, a2);
}

// 0x4E4200
int8 CAEPedSpeechAudioEntity::GetSexFromModel(int32 a1) {
    return plugin::CallMethodAndReturn<int8, 0x4E4200, CAEPedSpeechAudioEntity*, int32>(this, a1);
}

// 0x4E3F50
bool CAEPedSpeechAudioEntity::GetPedTalking() {
    return m_IsInitialized && m_IsPlayingSpeech;
}

// 0x4E4170
int8 CAEPedSpeechAudioEntity::GetVoiceAndTypeForSpecialPed(uint32 modelNameHash) {
    return plugin::CallMethodAndReturn<int8, 0x4E4170, CAEPedSpeechAudioEntity*, uint32>(this, modelNameHash);
}

// 0x4E3520
void CAEPedSpeechAudioEntity::UpdateParameters(CAESound* sound, int16 curPlayPos) {
    plugin::CallMethod<0x4E3520, CAEPedSpeechAudioEntity*, CAESound*, int16>(this, sound, curPlayPos);
}

// 0x4E4F70
void CAEPedSpeechAudioEntity::AddScriptSayEvent(int32 a1, int32 a2, uint8 a3, uint8 a4, uint8 a5) {
    plugin::CallMethod<0x4E4F70, CAEPedSpeechAudioEntity*, int32, int32, uint8, uint8, uint8>(this, a1, a2, a3, a4, a5);
}

// 0x4E5670
void CAEPedSpeechAudioEntity::Terminate() {
    plugin::CallMethod<0x4E5670, CAEPedSpeechAudioEntity*>(this);
}

// 0x4E5CD0
void CAEPedSpeechAudioEntity::PlayLoadedSound() {
    plugin::CallMethod<0x4E5CD0, CAEPedSpeechAudioEntity*>(this);
}

// 0x4E4120
int16 CAEPedSpeechAudioEntity::GetAllocatedVoice() {
    return m_VoiceID;
}

// 0x4E5800
bool CAEPedSpeechAudioEntity::WillPedChatAboutTopic(int16 topic) {
    switch (topic) {
    case 0:  return CanPedSayGlobalContext(48);
    case 1:  return CanPedSayGlobalContext(49);
    case 2:  return CanPedSayGlobalContext(50);
    case 3:  return CanPedSayGlobalContext(51);
    case 4:  return CanPedSayGlobalContext(52);
    case 5:  return CanPedSayGlobalContext(53);
    case 6:  return CanPedSayGlobalContext(54);
    case 7:  return CanPedSayGlobalContext(55);
    case 8:
    case 9:  return true;
    default: return false;
    }
}

// 0x4E4130
int16 CAEPedSpeechAudioEntity::GetPedType() {
    if (m_IsInitialized)
        return m_PedAudioType;
    else
        return -1;
}

// 0x4E4150
bool CAEPedSpeechAudioEntity::IsPedFemaleForAudio() {
    if (m_IsInitialized)
        return m_IsFemale;
    else
        return false;
}

int32 CAEPedSpeechAudioEntity::GetFreeSpeechSlot() {
    for (auto&& [i, ss] : notsa::enumerate(s_PedSpeechSlots)) {
        if (ss.Status == CAEPedSpeechSlot::eStatus::FREE) {
            return i;
        }
    }
    return -1;
}

uint32& CAEPedSpeechAudioEntity::GetNextPlayTimeRef(eGlobalSpeechContext gCtx) {
    return IsGlobalContextPain(gCtx)
        ? m_NextTimeCanSayPain[gCtx - GCTX_PAIN_START + 1]
        : gGlobalSpeechContextNextPlayTime[gCtx];
}

// 0x4E4F10
CAEPedSpeechAudioEntity* CAEPedSpeechAudioEntity::Constructor() {
    this->CAEPedSpeechAudioEntity::CAEPedSpeechAudioEntity();
    return this;
}

// notsa
const tSpeechContextInfo* CAEPedSpeechAudioEntity::GetSpeechContextInfo(eGlobalSpeechContext gCtx) {
    const auto& e = gSpeechContextLookup[gCtx];
    assert(e.GCtx == gCtx); // If ever triggered we'll need to use a for loop and search for `GCtx` manually
    return &e;
}
