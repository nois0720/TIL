# SFTP, Secure FTP, FTPS의 차이

보안을 위해 ftp를 사용하지 않고 보통 SFTP, Secure FTP, FTPS등을 사용한다. 그럼 세 가지 방법의 차이점은 뭘까

## SFTP (SSH File Transfer Protocol)

STFP는 사실 FTP를 사용하지 않는다. SFTP는 SSH 기반의 새로운 파일 전송 프로토콜이다. 따라서 SSH 서버가 구축되어 있어야 하며 SSH를 이용하기 때문에 구축, 유지에 비용이 적게 들어가고 Secure FTP나 FTPS에 비해 사용하기가 쉽다.

가장 많이 사용하는 SFTP의 예는 FileZilla, SSH Secure Shell, pscp, WinSCP등이 있다.

## Secure FTP (FTP over SSH)

SSH connection 위에 일반 FTP 터널링을 한 방법으로 접속 시 계정 정보는 암호화되지만 데이터는 암호화되지 않는다. 이 방법은 ssh를 이용하여 터널링 구성을 한 후에 일반 FTP로 데이터를 전송하는 방법이기 때문에 구축이 조금 어렵다.

## FTPS (FTP over SSL)

FTPS는 FTP에 TLS(Transport layer Security)와 Secure Socket Layer (SSL) 암호화 프로토콜이 더해진 방법이다. SSL 레이어에서 FTP가 동작하므로 커맨드와 데이터 모두가 암호화된다.
