PORTNAME=	openldap
PORTVERSION=	2.4.44
DISTVERSIONSUFFIX=	-25.el7_9
PORTREVISION=	3
CATEGORIES=	net linux

MAINTAINER=	emulation@FreeBSD.org
COMMENT=	LDAP libraries (Linux CentOS ${LINUX_DIST_VER})
WWW=		https://www.OpenLDAP.org/

USES=		cpe linux:c7
USE_LDCONFIG=	yes
USE_LINUX=	cyrus-sasl2 nspr nss
USE_LINUX_RPM=	yes

CONFLICTS=	linux-c6-${PORTNAME}
DESCR=		${.CURDIR}/../${PORTNAME}25-server/pkg-descr

OPTIONS_DEFINE=	DOCS

# do not install any openldap configuration directories/files
post-patch:
	@${RM} -r ${WRKSRC}/etc

# use a native openldap configuration directories/files
post-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/etc
	${LN} -sf ${LOCALBASE}/etc/openldap ${STAGEDIR}${PREFIX}/etc/openldap

.include <bsd.port.mk>
