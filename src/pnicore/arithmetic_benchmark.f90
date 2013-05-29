module arithmetic_benchmark
    implicit none
    save

    real(kind = 8),dimension(:,:),allocatable,private :: a
    real(kind = 8),dimension(:,:),allocatable,private :: b
    real(kind = 8),dimension(:,:),allocatable,private :: c
    real(kind = 8),dimension(:,:),allocatable,private :: d
    real(kind = 8),dimension(:,:),allocatable,private :: e
    real(kind = 8),dimension(:,:),allocatable,private :: f
    contains

        !----------------------------------------------------------------------
        subroutine run_add()
            implicit none
            c = a + b
        end subroutine run_add

        !----------------------------------------------------------------------
        subroutine run_sub()
            implicit none
            c = a - b
        end subroutine run_sub

        !----------------------------------------------------------------------
        subroutine run_mult()
            implicit none

            c = a*b
        end subroutine run_mult

        !----------------------------------------------------------------------
        subroutine run_div()
            implicit none

            c = a/b
        end subroutine run_div

        !----------------------------------------------------------------------
        subroutine run_all()
            implicit none

            c = a*b + (e-f)/d
        end subroutine run_all

        !-----------------------------------------------------------------------
        subroutine allocate_arithmetics(nx,ny)
            implicit none
            integer,intent(in) :: nx,ny
            integer :: mem_status
    
            !deallocate memory if necessary
            call deallocate_arithmetics()

            allocate(a(nx,ny),stat=mem_status)
            allocate(b(nx,ny),stat=mem_status)
            allocate(c(nx,ny),stat=mem_status)
            allocate(d(nx,ny),stat=mem_status)
            allocate(e(nx,ny),stat=mem_status)
            allocate(f(nx,ny),stat=mem_status)

            call initialize_data(nx,ny)

        end subroutine allocate_arithmetics

        !-----------------------------------------------------------------------
        subroutine initialize_data(nx,ny)
            implicit none
            integer,intent(in) :: nx,ny
            integer :: i,j
            real(kind = 8) :: rval

            call random_seed()
            do j = 1,ny
                do i = 1,nx
                   call random_number(rval)
                   a(i,j) = rval*huge(rval)

                   call random_number(rval)
                   b(i,j) = rval*huge(rval)

                   call random_number(rval)
                   c(i,j) = rval*huge(rval)

                   call random_number(rval)
                   d(i,j) = rval*huge(rval)

                   call random_number(rval)
                   e(i,j) = rval*huge(rval)

                   call random_number(rval)
                   f(i,j) = rval*huge(rval)
                end do
            end do

        end subroutine initialize_data
            

        !-----------------------------------------------------------------------
        subroutine deallocate_arithmetics()
            implicit none
            integer :: mem_status

            if (allocated(a)) then
                deallocate(a,stat=mem_status)
            end if

            if (allocated(b)) then
                deallocate(b,stat=mem_status)
            end if

            if (allocated(c)) then
                deallocate(c,stat=mem_status)
            end if

            if (allocated(d)) then
                deallocate(d,stat=mem_status)
            end if

            if (allocated(e)) then
                deallocate(e,stat=mem_status)
            end if

            if (allocated(f)) then
                deallocate(f,stat=mem_status)
            end if
        end subroutine deallocate_arithmetics

end module arithmetic_benchmark
