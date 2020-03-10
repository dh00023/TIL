# Instagram API 연동하기

## FACEBOOK 개발자 앱 설정하기

## 데이터 가져오기

```
curl -X POST \ https://api.instagram.com/oauth/access_token/ \ -F client_id=631278744307902 \ -F client_secret=ac811fd355d0806ab81b20b4281a5f94 \ -F grant_type=authorization_code \ -F redirect_uri=https://local-display.com:8000/ \ -F code=AQApP_V-OpbawRXi4Nc5pVoBEa4o9EXhMNUAJSrzoy7gafnpVJTRYAWXnvPFPQuHWemkLNKwwhAVVCB3G4-Cz5KwgNo38qgAfypZurkVBeihzHjMj59dw7Oz-5PD132Xhosh4xxXNxZBLtZ9gQrKkwQDtI_BMdDSwFKSg0uUi_XNkDuddPmt_hb6GpSUlZz1Mvs-WB-Qv0AXZvDiwxPrynVw0aDFCSaw39yGtSAwJHE8rg
```

```
https://www.instagram.com/oauth/authorize?client_id=631278744307902&redirect_uri=https://local-display.cjmall.com:8000/&scope=user_profile,user_media&response_type=code
```

```
https://local-display.cjmall.com:8000/styleshare/instagram?code=AQBmmYNfQyADOc1a9xNlnHl8vrIGWq40hUP6-hatmTwl2OxZ-qKQV5HeqctgXN2iresikwf4-Z-hCgXPSGV8EgjJAelXH-HkRchpMF8FzsP7mZ07FeWhSJJLUIlF-zZTLRCHoyfoLKHgEKhUqR_Ru0Yvwkr3zX5bzAit3nkm1vM_WTmvrZOaaidypfQWUBRafD3pIWhfHPq3PxtgPwVnHpJ-_RNEakvQNZhWY3HcZF_jEw#_
```



```
curl https://api.instagram.com/oauth/access_token/ POST -d "client_id=631278744307902 \ -F client_secret=ac811fd355d0806ab81b20b4281a5f94 \ -F grant_type=authorization_code \ -F redirect_uri=https://local-display.com:8000/ \ -F code=AQApP_V-OpbawRXi4Nc5pVoBEa4o9EXhMNUAJSrzoy7gafnpVJTRYAWXnvPFPQuHWemkLNKwwhAVVCB3G4-Cz5KwgNo38qgAfypZurkVBeihzHjMj59dw7Oz-5PD132Xhosh4xxXNxZBLtZ9gQrKkwQDtI_BMdDSwFKSg0uUi_XNkDuddPmt_hb6GpSUlZz1Mvs-WB-Qv0AXZvDiwxPrynVw0aDFCSaw39yGtSAwJHE8rg"
```

```
{
    "access_token": "IGQVJYSGlkLXJIVDdwdkVBaWhROHZABYXhxcmstVnBVODZA0MXVlYmV1ZAmJnV0xPUkswcHZAhb1dwN2tOQUQ5TkMtTl9QUEcwZAi1CdzNFSEhkaFpVVXNWMjlmTDJyYlpSc2xxQXFPZAmtqa0laSnZAyTWxVU0Q4TVBRN2NPemZAr",
    "user_id": 17841400671991673
}
```

```
curl -X GET \ 'https://graph.instagram.com/{user-id}?fields=id,username&access_token={access-token}'
```

```
https://graph.instagram.com/me/media?fields=id,username,media_type,media_url&access_token=IGQVJYSGlkLXJIVDdwdkVBaWhROHZABYXhxcmstVnBVODZA0MXVlYmV1ZAmJnV0xPUkswcHZAhb1dwN2tOQUQ5TkMtTl9QUEcwZAi1CdzNFSEhkaFpVVXNWMjlmTDJyYlpSc2xxQXFPZAmtqa0laSnZAyTWxVU0Q4TVBRN2NPemZAr
```

https://stackoverflow.com/questions/37420259/parsing-query-string-using-regular-expression-in-python



Url 정규표현식 변경하기

Processed: 2193043 rows; Rate:    3555 rows/s; Avg. rate:   16437 rows/s
2193043 rows exported to 1 files in 2 minutes and 13.430 seconds.