PORTNAME=	aws-sdk
PORTVERSION=	2.11.632
CATEGORIES=	devel rubygems
MASTER_SITES=	RG
PKGNAMESUFFIX=	2

MAINTAINER=	sunpoet@FreeBSD.org
COMMENT=	AWS SDK for Ruby
WWW=		https://github.com/aws/aws-sdk-ruby

LICENSE=	APACHE20

RUN_DEPENDS=	rubygem-aws-sdk-resources2>=${PORTVERSION}:devel/rubygem-aws-sdk-resources2

USES=		gem

NO_ARCH=	yes

PORTSCOUT=	limit:^2\.

.include <bsd.port.mk>
