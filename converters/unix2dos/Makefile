PORTNAME=	unix2dos
PORTVERSION=	1.3
PORTREVISION=	1
CATEGORIES=	converters
MASTER_SITES=	LOCAL/ehaupt

MAINTAINER=	obonilla@galileo.edu
COMMENT=	Convert ASCII newlines between CR/LF and LF

PLIST_FILES=	bin/dos2unix bin/unix2dos \
		man/man1/unix2dos.1.gz man/man1/dos2unix.1.gz
NO_WRKSUBDIR=	yes

CONFLICTS_INSTALL=	dos2unix

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/unix2dos ${STAGEDIR}${PREFIX}/bin/unix2dos
	${LN} -f ${STAGEDIR}${PREFIX}/bin/unix2dos ${STAGEDIR}${PREFIX}/bin/dos2unix
	${INSTALL_MAN} ${WRKSRC}/man1/unix2dos.1 ${STAGEDIR}${MANPREFIX}/man/man1
	${INSTALL_MAN} ${WRKSRC}/man1/dos2unix.1 ${STAGEDIR}${MANPREFIX}/man/man1

.include <bsd.port.mk>
