# Provide support for ports requiring ksh.  This includes flavors with proper
# dependencies and useful variables.
#
# Feature:	ksh
# Usage:	USES=ksh or USES=ksh:args
# Valid ARGS:	build, run, noflavors
#
# build		Indicates that ksn is required at build time.
# run		Indicates that ksn is required at run time.
# noflavors	Prevents flavors.  This is implied when there is no run
#               dependency on ksn.
#
# If build and run are omitted from the argument list, ksh will be added to
# BUILD_DEPENDS and RUN_DEPENDS.  KSH_NO_DEPENDS can be set to prevent both
# dependencies.
#
# Variables, which can be set in make.conf:
# DEFAULT_VERSIONS+=          The default flavor for ksh ports (ports with
#                             USES=ksh, but not the ksh ports themselves)
#                             can be added to DEFAULT_VERSIONS.  For example,
#                             DEFAULT_VERSIONS+= ksh=pdksh
#                             Valid flavors: ksh ksh-devel ksh93 ast-ksh pdksh mksh oksh
#                             Flavors specified on the command line take
#                             precedence.
#
# Variables, which can be set by ports:
# KSH_FLAVORS_EXCLUDE:      Do NOT build these ksh flavors.
#                             If KSH_FLAVORS_EXCLUDE is not defined and
#                               - there is a run dependency on ksh
#                               - the noflavors argument is not specified
#                             then all valid ksh flavors are assumed.
#
# KSH_NO_DEPENDS:           Do NOT add build or run dependencies on ksh.
#                             This will prevent flavors.
#
# Variables, which can be read by ports:
# KSH_CMD:                  ksh command with full path (e.g. /usr/local/bin/ksh)
# KSH_FLAVOR:               Used for dependencies (e.g. BUILD_DEPENDS= x11/cde>0:shells/${KSH_FLAVOR})
# KSH_PKGNAMESUFFIX:        PKGNAMESUFFIX to distinguish ksh flavors
#-------------------------------------------------------------------------------
#
# MAINTAINER:	cy@FreeBSD.org

.if !defined(_INCLUDE_USES_KSH_MK)
_INCLUDE_USES_KSH_MK=	yes

# Make sure that no dependency or some other environment variable
# pollutes the build/run dependency detection
.undef _KSH_BUILD_DEP
.undef _KSH_RUN_DEP
.undef _KSH_NOFLAVORS
_KSH_ARGS=		${ksh_ARGS:S/,/ /g}
.  if ${_KSH_ARGS:Mbuild}
_KSH_BUILD_DEP=	yes
_KSH_ARGS:=		${_KSH_ARGS:Nbuild}
.  endif
.  if ${_KSH_ARGS:Mrun}
_KSH_RUN_DEP=		yes
_KSH_ARGS:=		${_KSH_ARGS:Nrun}
.  endif
.  if ${_KSH_ARGS:Mnoflavors}
_KSH_NOFLAVORS=	yes
_KSH_ARGS:=		${_KSH_ARGS:Nnoflavors}
.  endif

# If the port does not specify a build or run dependency, and does not define
# KSH_NO_DEPENDS, assume both dependencies are required.
.  if !defined(_KSH_BUILD_DEP) && !defined(_KSH_RUN_DEP) && \
	!defined(KSH_NO_DEPENDS)
_KSH_BUILD_DEP=	yes
_KSH_RUN_DEP=		yes
.  endif

# Only set FLAVORS when...
.  if defined(_KSH_RUN_DEP) && !defined(_KSH_NOFLAVORS)
FLAVORS=	 ksh ksh-devel ksh93 ast-ksh pdksh mksh oksh
# Sort the default to be first
.    if defined(KSH_DEFAULT)
FLAVORS:=	${KSH_DEFAULT} ${FLAVORS:N${KSH_DEFAULT}}
.    endif
.    for flavor in ${KSH_FLAVORS_EXCLUDE}
FLAVORS:=	${FLAVORS:N${flavor}}
.    endfor
.  endif

# Only set FLAVOR when...
.  if defined(_KSH_RUN_DEP) && !defined(_KSH_NOFLAVORS) && empty(FLAVOR)
.    if defined(KSH_DEFAULT)
FLAVOR=	${KSH_DEFAULT}
.    else
FLAVOR=	${FLAVORS:[1]}
.    endif # defined(KSH_DEFAULT)
.  endif # !defined(_KSH_NOFLAVORS) && defined(_KSH_RUN_DEP) && empty(FLAVOR)

.  if !empty(FLAVOR)
KSH_FLAVOR=	${FLAVOR}
.  else
KSH_FLAVOR=	pdksh
.  endif

.  if ${FLAVOR:Mmksh}
KSH_PORTDIR=		shells/mksh
KSH_PORT_NAME=		mksh
KSH_CMD=		${PREFIX}/bin/mksh
.  elif ${FLAVOR:Moksh}
KSH_PORTDIR=		shells/oksh
KSH_PORT_NAME=		oksh
KSH_CMD=		${PREFIX}/bin/oksh
.  elif ${FLAVOR:Mast-ksh}
KSH_PORTDIR=		shells/ast-ksh
KSH_PORT_NAME=		ast-ksh
KSH_CMD=		${PREFIX}/bin/ksh93
.  elif ${FLAVOR:Mksh93}
KSH_PORTDIR=		shells/ksh93
KSH_PORT_NAME=		ksh93
KSH_CMD=		${PREFIX}/bin/ksh93
.  elif ${FLAVOR:Mksh-devel}
KSH_PORTDIR=		shells/ksh-devel
KSH_PORT_NAME=		ksh-devel
KSH_CMD=		${PREFIX}/bin/ksh93
.  elif ${FLAVOR:Mksh}
KSH_PORTDIR=		shells/ksh
KSH_PORT_NAME=		ksh
KSH_CMD=		${PREFIX}/bin/ksh93
.  else
KSH_PORTDIR=		shells/pdksh
KSH_PORT_NAME=		pdksh
KSH_CMD=		${PREFIX}/bin/ksh
.  endif


KSH_PKGNAMESUFFIX=	-${KSH_PORT_NAME}

.  if defined(_KSH_BUILD_DEP)
BUILD_DEPENDS+=		${KSH_CMD}:${KSH_PORTDIR}@${KSH_FLAVOR}
.  endif
.  if defined(_KSH_RUN_DEP)
RUN_DEPENDS+=	${KSH_CMD}:${KSH_PORTDIR}@${KSH_FLAVOR}
.  endif

MAKE_ARGS+=	KSH=${KSH_CMD}

.endif # _INCLUDE_USES_KSH_MK
