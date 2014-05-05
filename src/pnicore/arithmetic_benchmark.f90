!
! (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
!
! This file is part of pni-benchmarks.
!
! pni-benchmarks is free software: you can redistribute it and/or modify
! it under the terms of the GNU General Public License as published by
! the Free Software Foundation, either version 2 of the License, or
! (at your option) any later version.
!
! pni-benchmarks is distributed in the hope that it will be useful,
! but WITHOUT ANY WARRANTY; without even the implied warranty of
! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
! GNU General Public License for more details.
!
! You should have received a copy of the GNU General Public License
! along with pni-benchmarks.  If not, see <http://www.gnu.org/licenses/>.
! ===========================================================================
!
!  Created on: May 30, 2013
!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
!
module arithmetic_benchmark
    use iso_c_binding
    implicit none
    save
   
    real(kind=8),dimension(:,:),allocatable :: a
    real(kind=8),dimension(:,:),allocatable :: b
    real(kind=8),dimension(:,:),allocatable :: c
    real(kind=8),dimension(:,:),allocatable :: d
    real(kind=8),dimension(:,:),allocatable :: e
    real(kind=8),dimension(:,:),allocatable :: f
    real(kind=8) :: s
    contains
        
        !----------------------------------------------------------------------
        subroutine deallocate_data() bind(C,name="deallocate_data")
            implicit none
            integer :: mem_status

            if (allocated(a)) then
               deallocate(a,stat=mem_status) 
            end if

            if(allocated(b)) then
                deallocate(b,stat=mem_status)
            end if

            if(allocated(c)) then
                deallocate(c,stat=mem_status)
            end if

            if(allocated(d)) then
                deallocate(d,stat=mem_status)
            end if

            if(allocated(e)) then
                deallocate(e,stat=mem_status)
            end if

            if(allocated(f)) then
                deallocate(f,stat=mem_status)
            end if

        end subroutine deallocate_data
        
        !----------------------------------------------------------------------
        subroutine init_data(nx,ny) bind(C,name="init_data")
            implicit none
            integer(C_INT) :: nx,ny,i,j
            real(kind = 8) :: rval

            !initialize the random number generator
            call random_seed()

            !initialize all array members with random numbers
            do i=1,nx
                do j=1,ny
                    call random_number(rval)
                    a(i,j) = rval*huge(rval)

                    call random_number(rval)
                    b(i,j) = rval*huge(rval)

                    call random_number(rval)
                    b(i,j) = rval*huge(rval)

                    call random_number(rval)
                    d(i,j) = rval*huge(rval)

                    call random_number(rval)
                    e(i,j) = rval*huge(rval)
                    
                    call random_number(rval)
                    f(i,j) = rval*huge(rval)
                end do
            end do

            call random_number(rval)
            s = rval*huge(rval)

        end subroutine init_data

        !----------------------------------------------------------------------
        subroutine allocate_data(nx,ny) bind(C,name="allocate_data")
            implicit none
            integer(C_INT),intent(in),value :: nx,ny
            integer :: mem_status
            
            call deallocate_data()

            allocate(a(nx,ny),stat=mem_status)
            allocate(b(nx,ny),stat=mem_status)
            allocate(c(nx,ny),stat=mem_status)
            allocate(d(nx,ny),stat=mem_status)
            allocate(e(nx,ny),stat=mem_status)
            allocate(f(nx,ny),stat=mem_status)

            call init_data(nx,ny);

        end subroutine allocate_data

        !----------------------------------------------------------------------
        subroutine binary_run_add() bind(C,name="binary_run_add")
            implicit none
            c = a + b
        end subroutine binary_run_add

        !----------------------------------------------------------------------
        subroutine unary_run_add_array() bind(C,name="unary_run_add_array")
            implicit none
            a = a+c
        end subroutine 

        !----------------------------------------------------------------------
        subroutine unary_run_add_scalar() bind(C,name="unary_run_add_scalar")
            implicit none
            a = a+s
        end subroutine

        !----------------------------------------------------------------------
        subroutine binary_run_sub() bind(C,name="binary_run_sub")
            implicit none
            c = a - b
        end subroutine binary_run_sub

        !----------------------------------------------------------------------
        subroutine unary_run_sub_array() bind(C,name="unary_run_sub_array")
            implicit none
            a = a-c
        end subroutine

        !----------------------------------------------------------------------
        subroutine unary_run_sub_scalar() bind(C,name="unary_run_sub_scalar")
            implicit none
            a = a-s
        end subroutine

        !----------------------------------------------------------------------
        subroutine binary_run_mult() bind(C,name="binary_run_mult")
            implicit none
            c = a*b
        end subroutine binary_run_mult

        !----------------------------------------------------------------------
        subroutine unary_run_mult_array() bind(C,name="unary_run_mult_array")   
            implicit none
            a = a*c
        end subroutine

        !----------------------------------------------------------------------
        subroutine unary_run_mult_scalar() bind(C,name="unary_run_mult_scalar")
            implicit none
            a = a*s
        end subroutine

        !----------------------------------------------------------------------
        subroutine binary_run_div() bind(C,name="binary_run_div")
            implicit none
            c = a/b
        end subroutine binary_run_div

        !----------------------------------------------------------------------
        subroutine unary_run_div_array() bind(C,name="unary_run_div_array")
            implicit none
            a = a/c
        end subroutine

        !----------------------------------------------------------------------
        subroutine unary_run_div_scalar() bind(C,name="unary_run_div_scalar")
            implicit none
            a = a/s
        end subroutine

        !----------------------------------------------------------------------
        subroutine binary_run_all() bind(C,name="binary_run_all")
            implicit none
            c = a*b + (e-f)/d
        end subroutine binary_run_all

        !----------------------------------------------------------------------

end module arithmetic_benchmark
