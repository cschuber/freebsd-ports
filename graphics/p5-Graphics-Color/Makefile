PORTNAME=	Graphics-Color
PORTVERSION=	0.31
CATEGORIES=	graphics perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	perl@FreeBSD.org
COMMENT=	Device and library agnostic color spaces
WWW=		https://metacpan.org/release/Graphics-Color

LICENSE=	ART10 GPLv1+
LICENSE_COMB=	dual

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	p5-Color-Library>=0.020:graphics/p5-Color-Library \
		p5-Moose>=0.74:devel/p5-Moose \
		p5-MooseX-Aliases>=0.03:devel/p5-MooseX-Aliases \
		p5-MooseX-Clone>=0.03:devel/p5-MooseX-Clone \
		p5-MooseX-Storage>=0.23:devel/p5-MooseX-Storage \
		p5-MooseX-Types>=0.19:devel/p5-MooseX-Types
TEST_DEPENDS=	p5-Test-Number-Delta>=0:devel/p5-Test-Number-Delta

USES=		perl5
USE_PERL5=	configure

NO_ARCH=	yes

.include <bsd.port.mk>
