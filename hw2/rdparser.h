void error(char *where);
void match(int token);

//  PLIST      :  PROD PLIST_MORE           {NT}
void PLIST();

//  PLIST_MORE :  PROD PLIST_MORE           {NT}
//  PLIST_MORE :  e                         {$}
void PLIST_MORE();

//  PBODY      :  RULE PBODY_MORE           {NT,T,EOL}
void PBODY();

//  PBODY_MORE :  OR RULE PBODY_MORE        {OR}
//  PBODY_MORE :  e                         {SEMI}
void PBODY_MORE();

//  PROD       :  NT GOES PBODY SEMI E_EOL  {NT}
void PROD();

//  RULE       :  NT RULE                   {NT}
//  RULE       :  T RULE                    {T}
//  RULE       :  EOL                       {EOL}
void RULE();
