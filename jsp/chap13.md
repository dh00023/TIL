# 파일업로드

## 파일 업로드 라이브러리 설치

[http://www.servlets.com/cos/](http://www.servlets.com/cos/) 에서 [**cos-26Dec2008.zip**](http://www.servlets.com/cos/cos-26Dec2008.zip) 을 다운받는다.

```
- /doc
- /lib
 ㄴ cos.jar
- /src
```

다운로드 받은후 압축을 해제하면 `/lib` 폴더에 `cos.jar` 파일이 있다.

이 파일을 현재 실행중인 프로젝트의 `/WebContent/WEB-INF/lib` 폴더 안에 집어넣는다.



## 파일 업로드하기

파일을 업로드 하면 저장이 될 폴더를 `WebContent` 안에 생성해준다.

```jsp
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
	<form action="fileFormOk.jsp" method="post" enctype="multipart/form-data">
		파일 : <input type="file" name="file">
		<input type="submit" value="제출">
	</form>

</body>
</html>
```

```jsp
<%@page import="java.util.Enumeration"%>
<%@page import="com.oreilly.servlet.multipart.DefaultFileRenamePolicy"%>
<%@page import="com.oreilly.servlet.MultipartRequest"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
       
<%
	//실제 파일이 저장되는 경로
	String path = request.getRealPath("fileFolder");

	int size = 1024*1024*10; //10M까지 파일 사이즈 가능
	String file = "";
	String originFile="";
	
	try{
		MultipartRequest mult = new MultipartRequest(request, path, size, "UTF-8", new DefaultFileRenamePolicy());
		
		Enumeration files = mult.getFileNames();
		String str = (String)files.nextElement();
		
		file = mult.getFilesystemName(str);
		originFile = mult.getOriginalFileName(str);
		
	}catch(Exception e){
		e.printStackTrace();
	}

%>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
<%= file %>
<%= originFile %>
file upload success!
</body>
</html>
```



실제로 파일이 올라가는 곳은 eclipse상 경로가 아닌 서버 내부에 올라간다.



