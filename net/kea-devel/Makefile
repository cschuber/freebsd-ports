PORTNAME=	kea
PORTVERSION=	${ISCVERSION:S/-P/P/:S/-beta/b/:S/a/.a/:S/rc/.rc/}
CATEGORIES=	net

MAINTAINER=	cy@FreeBSD.org
COMMENT=	ISC DHCPD replacing isc-dhcpd tracking development branch
WWW=		https://kea.isc.org/

LICENSE=	MPL20
LICENSE_FILE=	${WRKSRC}/COPYING

DOCS_BUILD_DEPENDS=	sphinx-build:textproc/py-sphinx \
		${NONEXISTENT}:textproc/py-sphinx_rtd_theme
LIB_DEPENDS=	liblog4cplus.so:devel/log4cplus \
		libboost_system.so:devel/boost-libs

USES=		autoreconf compiler:c++11-lang iconv libtool pathfix ssl cpe

# ISC releases things like 1.4.0-P1, which our versioning doesn't like
ISCVERSION=	2.3.1
ISC_COMMIT=	727340248c71a0ca5549b987c09ca761e786fb5b

USE_GITLAB=	yes
GL_SITE=	https://gitlab.isc.org
GL_ACCOUNT=	isc-projects
GL_COMMIT=	Kea-${PORTVERSION}

CPE_VENDOR=	isc
CPE_VERSION=	${ISCVERSION:C/-.*//}
.if ${ISCVERSION:M*-*}
CPE_UPDATE=	${ISCVERSION:C/.*-//:tl}
.endif

WRKSRC=		${WRKDIR}/${PORTNAME}-Kea-${ISCVERSION}-${ISC_COMMIT}
USE_LDCONFIG=	yes
USE_RC_SUBR=	${PORTNAME}
GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--with-openssl=${OPENSSLBASE} \
		--with-log4cplus=${LOCALBASE} \
		--with-boost-include=${LOCALBASE}/include \
		--with-boost-lib-dir=${LOCALBASE}/lib \
		--without-werror
INSTALL_TARGET=	install-strip
TEST_TARGET=	check

PORTDOCS=	AUTHORS COPYING ChangeLog README \
		CONTRIBUTING.md examples code_of_conduct.md \
		platforms.rst

OPTIONS_DEFINE=	DOCS MYSQL PGSQL SHELL
OPTIONS_SUB=	yes
MYSQL_USES=	mysql
MYSQL_CONFIGURE_ON=	--with-mysql=${LOCALBASE}/bin/mysql_config
MYSQL_CONFIGURE_OFF=	--without-mysql
MYSQL_SUB_LIST=		REQ_MYSQL=mysql
MYSQL_SUB_LIST_OFF=	REQ_MYSQL=""
PGSQL_USES=	pgsql
WANT_PGSQL=	client
PGSQL_CONFIGURE_ON=	--with-pgsql=${LOCALBASE}/bin/pg_config
PGSQL_CONFIGURE_OFF=	--without-pgsql
PGSQL_SUB_LIST=		REQ_PGSQL=postgresql
PGSQL_SUB_LIST_OFF=	REQ_PGSQL=""
SHELL_DESC=	Install kea-shell(8) (Python)
SHELL_USES=	python:3.5+
SHELL_CONFIGURE_ON=	--enable-shell
DOCS_CONFIGURE_ON=	--enable-generate-docs

.include <bsd.port.mk>
