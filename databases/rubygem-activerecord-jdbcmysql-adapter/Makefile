PORTNAME=	activerecord-jdbcmysql-adapter
PORTVERSION=	51.0
CATEGORIES=	databases rubygems java
MASTER_SITES=	RG

MAINTAINER=	ruby@FreeBSD.org
COMMENT=	ActiveRecord driver for MySQL using JDBC running under JRuby
WWW=		https://github.com/jruby/activerecord-jdbc-adapter

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

RUN_DEPENDS=	jruby:lang/jruby \
		rubygem-activerecord-jdbc-adapter>=${PORTVERSION}:databases/rubygem-activerecord-jdbc-adapter \
		rubygem-jdbc-mysql>=5.1.36:databases/rubygem-jdbc-mysql

NO_ARCH=	yes
USES=		gem

.include <bsd.port.mk>
